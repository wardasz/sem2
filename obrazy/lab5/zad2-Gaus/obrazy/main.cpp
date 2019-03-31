#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cmath>
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
int robocza7;

int Gaus1;
int Gaus2;
int tresh1;
int tresh2;
int scale;
int delta;

void on_trackbar(int, void*)
{
	Gaus1 = robocza1;
	Gaus2 = robocza2;
	tresh1 = robocza3;
	tresh2 = robocza4;
	scale = robocza5;
	delta = robocza6;
}

int main() {

	Mat image;
	Mat image2;
	Mat image3;
	Mat image4;
	Mat image5;
	Mat image6;
	Mat image7;
	Mat image8;
	Mat image9;
	Mat image10;
	Mat image11;
	Mat image12;

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);
	namedWindow("window3", CV_WINDOW_AUTOSIZE);
	namedWindow("window4", CV_WINDOW_AUTOSIZE);
	namedWindow("window5", CV_WINDOW_AUTOSIZE);
	namedWindow("window6", CV_WINDOW_AUTOSIZE);
	namedWindow("window7", CV_WINDOW_AUTOSIZE);
	
	namedWindow("Suwaki", 4);
	createTrackbar("Gaus-wysokoœæ", "Suwaki", &robocza1, 20, on_trackbar);
	createTrackbar("Gaus-d³ugoœæ", "Suwaki", &robocza2, 20, on_trackbar);
	createTrackbar("Treshhold-dol", "Suwaki", &robocza3, 255, on_trackbar);
	createTrackbar("Treshhold-gora", "Suwaki", &robocza4, 255, on_trackbar);
	createTrackbar("Sobel-scale", "Suwaki", &robocza5, 20, on_trackbar);
	createTrackbar("Sobel-delta", "Suwaki", &robocza6, 20, on_trackbar);
	

	VideoCapture cap;
	cap.open(0);
	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 384);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

	while (1) {
		try {
			cap >> image;
			imshow("window", image);
			
			cvtColor(image, image2, CV_BGR2GRAY);
			CvSize rozmiar;
			rozmiar.width = (Gaus1*2)+1;
			rozmiar.height = (Gaus2 * 2) + 1;
			//image2 = zgausowane
			GaussianBlur(image2, image2, rozmiar, 0);

			//image 3,4-soble, 5,6-abs'y
			Sobel(image2, image3, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
			Sobel(image2, image4, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);
			convertScaleAbs(image3, image5); 
			convertScaleAbs(image4, image6);

			imshow("window3", image5);
			imshow("window4", image6);
			//image 7,8 - tresholdy
			threshold(image5, image7, tresh1, tresh2, CV_THRESH_BINARY);
			threshold(image6, image8, tresh1, tresh2, CV_THRESH_BINARY);
			imshow("window5", image7);
			imshow("window6", image8);

			//image9-suma
			addWeighted(image7, 1, image8, 2, 0.0, image9);
			imshow("window2", image9);

			image3.convertTo(image3, CV_32FC1);
			image4.convertTo(image4, CV_32FC1);
			image10.convertTo(image10, CV_32FC1);
			image11.convertTo(image11, CV_32FC1);
			//image 10 to magnituda, 11 to k¹ty
			cartToPolar(image3, image4, image10, image11, true);

			image9.copyTo(image12);
			cvtColor(image12, image12, CV_GRAY2BGR);
			
			Vec3b czern = (0, 0, 0);
			Vec3b kol1 = (255, 255, 255);
			Vec3b kol2 = (255, 0, 0);
			Vec3b kol3 = (0, 255, 0);
			Vec3b kol4 = (0, 0, 255);

			for (int i = 0; i < image9.rows; i++) {
				for (int j = 0; j < image9.cols; j++) {
					if (image12.at<Vec3b>(i, j) != czern && image11.at<float>(i, j) > 45 && image11.at<float>(i, j) <= 135) image12.at<Vec3b>(i, j) = kol1;
					if (image12.at<Vec3b>(i, j) != czern && image11.at<float>(i, j) > 135 && image11.at<float>(i, j) <= 225) image12.at<Vec3b>(i, j) = kol2;
					if (image12.at<Vec3b>(i, j) != czern && image11.at<float>(i, j) > 225 && image11.at<float>(i, j) <= 315) image12.at<Vec3b>(i, j) = kol3;
					if (image12.at<Vec3b>(i, j) != czern && image11.at<float>(i, j) > 315 && image11.at<float>(i, j) <= 360) image12.at<Vec3b>(i, j) = kol4;
				}
			}
			imshow("window7", image12);
			

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