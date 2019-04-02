#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

int robocza1;
int robocza2;
int robocza3;
int robocza4;
int robocza5;
int robocza6;

int hgora;
int hdol;
int sgora;
int sdol;
int vgora;
int vdol;

void on_trackbar(int, void*)
{
	hgora = robocza1;
	hdol = robocza2;
	sgora = robocza3;
	sdol = robocza4;
	vgora = robocza5;
	vdol = robocza6;
}

int main() {

	Mat image;
	Mat image2;
	Mat image3;
	Mat image4;
	Mat image5;
	Mat image6;
	VideoCapture cap;
	RNG rng(12345);

	namedWindow("Suwaki", 4);
	createTrackbar("Hgora", "Suwaki", &robocza1, 255, on_trackbar);
	createTrackbar("Hdol", "Suwaki", &robocza2, 255, on_trackbar);
	createTrackbar("Sgora", "Suwaki", &robocza3, 255, on_trackbar);
	createTrackbar("Sdul", "Suwaki", &robocza4, 255, on_trackbar);
	createTrackbar("Vgora", "Suwaki", &robocza5, 255, on_trackbar);
	createTrackbar("Vdol", "Suwaki", &robocza6, 255, on_trackbar);

	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);
	namedWindow("window3", CV_WINDOW_AUTOSIZE);
	namedWindow("window4", CV_WINDOW_AUTOSIZE);
	namedWindow("window5", CV_WINDOW_AUTOSIZE);
	namedWindow("window6", CV_WINDOW_AUTOSIZE);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 384);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

	while (1) {
		try {
			cap >> image;
			imshow("window", image);

			cvtColor(image, image2, CV_BGR2HSV);
			imshow("window2", image2);

			//ustalanie wartoœci
			inRange(image2, Scalar(hdol, sdol, vdol), Scalar(hgora, sgora, vgora), image3);
			imshow("window3", image3);

			erode(image3, image4, (3, 3));
			erode(image4, image4, (3, 3));
			imshow("window4", image4);		
			dilate(image4, image5, (8, 8));
			dilate(image5, image5, (8, 8));
			imshow("window5", image5);

			vector<vector<Point>> kontury;
			vector<Vec4i> hier;
			findContours(image5, kontury, hier, RETR_TREE, CHAIN_APPROX_SIMPLE);
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

			Mat drawing = Mat::zeros(image.size(), CV_8UC3);
			for (int i = 0; i < kontury.size(); i++)
			{
				Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
				drawContours(drawing, kontury, i, color, 2, 8, hier, 0, Point());
				circle(drawing, mc[i], 4, color, -1, 8, 0);
			}

			imshow("window6", drawing);
				
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