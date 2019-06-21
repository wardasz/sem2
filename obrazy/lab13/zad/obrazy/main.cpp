#include <opencv2/opencv.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "Panel Sterowania"

int main(int argc, const char *argv[])
{
	cv::Mat frame = cv::Mat(90, 250, CV_8UC3);

	cvui::init(WINDOW_NAME);

	bool wybrano = false;

	cv::Mat zrodlo;

	cv::VideoCapture cap;

	cv::namedWindow("film", CV_WINDOW_AUTOSIZE);

	while (true) {
		frame = cv::Scalar(49, 52, 49);

		
		if (cvui::button(frame, 20, 10, "Przetwarzaj obraz z kamery")) {
			cap.open(0);
			double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
			double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
			wybrano = true;
		}

		if (cvui::button(frame, 20, 50, "Przetwarzaj obraz z dysku")) {
			cap = cv::VideoCapture("D:\\klatki\\film.avi");
			wybrano = true;
		}

		cvui::imshow(WINDOW_NAME, frame);

		if (wybrano == true) {
			cap >> zrodlo;
			cv::imshow("film", zrodlo);
		}

		// Check if ESC key was pressed
		if (cv::waitKey(20) == 27) {
			break;
		}
	}

	return 0;
}