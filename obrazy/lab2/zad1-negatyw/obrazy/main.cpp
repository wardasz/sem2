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
	VideoCapture cap;

	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	while (1) {
		try {
			cap >> image;
			imshow("window", image);
			cvtColor(image, image2, CV_BGR2GRAY);
			imshow("window2", image2);
			image3 = image2;
			for (int i = 0; i < image2.rows; i++) {
				for (int j = 0; j < image2.cols; j++) {
					image3.at<uchar>(i, j) = 255 - image3.at<uchar>(i, j);
				}
			}
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