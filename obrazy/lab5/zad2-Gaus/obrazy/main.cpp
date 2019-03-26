#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cmath>
#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

int main() {

	Mat image;
	Mat image2;
	Mat image3;
	Mat image4;
	Mat image5; // = Mat(384, 288, CV_64F, 0.0);
	Mat image6;
	VideoCapture cap;

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

			cvtColor(image, image2, CV_BGR2GRAY);
			CvSize rozmiar;
			rozmiar.width = 5;
			rozmiar.height = 7;
			GaussianBlur(image2, image2, rozmiar, 0);
			imshow("window2", image2);

			Sobel(image2, image3, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
			convertScaleAbs(image3, image3);
			Sobel(image2, image4, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
			convertScaleAbs(image4, image4);
			imshow("window3", image3);
			imshow("window4", image4);

			//image5 = Mat::zeros(384, 288, CV_64F);
			//Mat image5 = image;
			image.copyTo(image5);
			for (int i = 50; i < 100; i++) {
				for (int j = 50; j < 100; j++) {
					//image5.at<uchar>(i, j) = sqrt(((image3.at<uchar>(i, j))*(image3.at<uchar>(i, j)))+((image4.at<uchar>(i, j))*(image4.at<uchar>(i, j))));
					image5.at<uchar>(i, j) = 255 - image5.at<uchar>(i, j);
				}
			}
			imshow("window5", image5);
			//addWeighted(image3, 0.5, image4, 0.5, 0, image5);
			//imshow("window5", image5);
			//threshold(image5, image6, 30, 255, CV_THRESH_BINARY);
			//imshow("window6", image6);


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