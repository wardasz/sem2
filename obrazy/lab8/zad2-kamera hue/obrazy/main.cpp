#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/video/background_segm.hpp>

#include<iomanip>
#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

int can1;
int can2;

int robocza1;
int robocza2;

void on_trackbar(int, void*)
{
	can1 = robocza1;
	can2 = robocza2;
}


int main() {

	Mat image; // obraz Ÿród³owy
	Mat image2; // maska MoG2
	Mat image3;
	Mat image4;
	Ptr<BackgroundSubtractor> mog; //MOG2 Background subtractor
	VideoCapture cap;

	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);
	namedWindow("window3", CV_WINDOW_AUTOSIZE);

	namedWindow("Suwaki", 4);
	createTrackbar("Canny1", "Suwaki", &robocza1, 200, on_trackbar);
	createTrackbar("Canny2", "Suwaki", &robocza2, 200, on_trackbar);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 384);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

	while (1) {
		try {
			cap >> image;
			imshow("window", image);

			Canny(image, image2, can1, can2);
			imshow("window2", image2);

			image.copyTo(image3);

			vector<Vec4i> lines;
			HoughLinesP(image2, lines, 1, CV_PI / 180, 50, 50, 10);
			for (size_t i = 0; i < lines.size(); i++)
			{
				Vec4i l = lines[i];
				line(image3, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
			}
			imshow("window3", image3);
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