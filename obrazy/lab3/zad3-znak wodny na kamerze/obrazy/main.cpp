#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

int main() {

	Mat image;
	Mat image2;
	Mat image3;
	VideoCapture cap;

	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);
	namedWindow("window3", CV_WINDOW_AUTOSIZE);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	image2 = imread("D:\\klatki\\logo.bmp", CV_LOAD_IMAGE_COLOR);

	while (1) {
		try {
			cap >> image;
			cap >> image3;
			imshow("window", image);

			imshow("window2", image2);

			Rect Rec(0, 0, 80, 64);
			Mat Roi = image(Rec);
			addWeighted(Roi, 1, image2, 2, 0.0, Roi);
			Rect WhereRec(0, 0, Roi.cols, Roi.rows);
			Roi.copyTo(image3(WhereRec));
			imshow("window3", image3);
		}
		catch (Exception e) {
			cap.open(1);
		}

		if (waitKey(15) == 27) {
			cap.release();
			cvDestroyAllWindows();
			break;
		}
	}

	return 0;
}