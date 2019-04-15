#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/video/background_segm.hpp>

#include<iomanip>
#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

int robocza1;
int robocza2;

int history;
int nmixtures;

Ptr<BackgroundSubtractorMOG2> mog; //MOG2 Background subtractor

void on_trackbar1(int, void*)
{
	history = robocza1;
	mog->setHistory(history);
}

void on_trackbar2(int, void*)
{
	nmixtures = robocza2;
	mog = createBackgroundSubtractorMOG2(history, 16, true);
	mog->setNMixtures(nmixtures);
}

int main() {

	Mat image; // obraz Ÿród³owy
	Mat image2; // maska MoG2
	Mat image3;
	Mat image4;
	VideoCapture cap;

	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);
	namedWindow("window3", CV_WINDOW_AUTOSIZE);
	namedWindow("window4", CV_WINDOW_AUTOSIZE);

	namedWindow("Suwaki", 4);
	createTrackbar("History", "Suwaki", &robocza1, 200, on_trackbar1);
	createTrackbar("Nmixtures", "Suwaki", &robocza2, 200, on_trackbar2);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 384);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

	mog = createBackgroundSubtractorMOG2(history, 16, true);
	while (1) {
		try {		

			cap >> image;
			imshow("window", image);

			mog->apply(image, image2);
			imshow("window2", image2);

			mog->getBackgroundImage(image3);
			imshow("window3", image3);

			vector<vector<Point>> kontury;
			vector<Vec4i> hier;
			findContours(image2, kontury, hier, RETR_TREE, CHAIN_APPROX_SIMPLE);
			vector<Moments> mu(kontury.size());
			for (int i = 0; i < kontury.size(); i++)
			{
				mu[i] = moments(kontury[i], false);
			}
			vector<Point2f> mc(kontury.size());
			for (int i = 0; i < kontury.size(); i++)
			{
				mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
			}

			image.copyTo(image4);
			for (int i = 0; i < kontury.size(); i++)
			{
				Scalar color = Scalar(0, 0, 255);
				drawContours(image4, kontury, i, color, 2, 8, hier, 0, Point());
				circle(image4, mc[i], 4, color, -1, 8, 0);
			}
			imshow("window4", image4);
			
		}
		catch (Exception e) {
			cap.release();
			cvDestroyAllWindows();
			break;
		}

		if (waitKey(15) == 27) {
			cap.release();
			cvDestroyAllWindows();
			break;
		}
	}

	return 0;
}