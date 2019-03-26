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
	Mat pierwsza;

	cv::VideoCapture capture("D:\\klatki\\robot_no_loop.avi");

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);
	namedWindow("window3", CV_WINDOW_AUTOSIZE);
	namedWindow("window4", CV_WINDOW_AUTOSIZE);
	bool czy = true;

	while (1) {
		try {
			capture >> image;
			cvtColor(image, image, CV_BGR2GRAY);
			imshow("window", image);

			if (czy == true) {
				pierwsza = image;
				czy = false;
			}		
			
			imshow("window2", pierwsza);

			absdiff(image, pierwsza, image2);
			imshow("window3", image2);

			threshold(image2, image3, 100, 255, CV_THRESH_BINARY);
			imshow("window4", image3);

		}
		catch (Exception e) {
			capture.release();
			cvDestroyAllWindows();
			break;
		}

		if (waitKey(15) == 27) {
			capture.release();
			cvDestroyAllWindows();
			break;
		}
	}

	return 0;
}