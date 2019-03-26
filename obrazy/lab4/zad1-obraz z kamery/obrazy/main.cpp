#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;


int main() {

	Mat image;
	Mat image2;
	Mat image3;
	Mat akumulator;
	Mat pierwsza;

	double alfa = 0.05;

	VideoCapture cap;

	cap.open(0);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);
	namedWindow("window3", CV_WINDOW_AUTOSIZE);
	namedWindow("window4", CV_WINDOW_AUTOSIZE);
	namedWindow("window5", CV_WINDOW_AUTOSIZE);

	bool czy = true;
	while (1) {
		try {
			cap >> image;
			cvtColor(image, image, CV_BGR2GRAY);
			imshow("window", image);

			if (czy == true) {
				image.copyTo(pierwsza);
			}

			imshow("window2", pierwsza);

			absdiff(image, pierwsza, image2);
			imshow("window3", image2);
			threshold(image2, image3, 30, 255, CV_THRESH_BINARY);
			imshow("window4", image3);
			if (czy == true) {
				czy = false;
				image3.copyTo(akumulator);
			}
			for (int i = 0; i < akumulator.rows; i++) {
				for (int j = 0; j < akumulator.cols; j++) {
					akumulator.at<uchar>(i, j) = (int)((1 - alfa)*akumulator.at<uchar>(i, j) + alfa * image3.at<uchar>(i, j));
				}
			}

			imshow("window5", akumulator);

		}
		catch (Exception e) {
			cap.release();
			cvDestroyAllWindows();
			break;
		}

		if (waitKey(40) == 27) {
			cap.release();
			cvDestroyAllWindows();
			break;
		}
	}
	return 0;
}

