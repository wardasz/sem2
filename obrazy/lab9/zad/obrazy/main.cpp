#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/video/tracking.hpp>
#include<opencv2/videoio.hpp>

#include<iostream>
#include<conio.h>
#include<ctype.h>

using namespace cv;
using namespace std;

int robocza1;
int robocza2;
int robocza3;

int rogi;
double jakosc;
double dystans;

void on_trackbar(int, void*)
{
	rogi = robocza1;
	jakosc = (double)robocza2/10;
	dystans = (double)robocza3;
}

int main() {

	Mat image;
	Mat szareStare;
	Mat szareNowe;
	Mat image2;
	VideoCapture cap;
	bool start = true;
	vector<Point2f> stare;
	vector<Point2f> nowe;
	
	namedWindow("Suwaki", 4);
	createTrackbar("maxCorners", "Suwaki", &robocza1, 100, on_trackbar);
	createTrackbar("qualityLevel,", "Suwaki", &robocza2, 10, on_trackbar);
	createTrackbar("minDistance", "Suwaki", &robocza3, 300, on_trackbar);

	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);
	//namedWindow("window3", CV_WINDOW_AUTOSIZE);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 384);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

	while (1) {
		try {
			if (rogi < 10) rogi = 10;
			if (jakosc < 0.1) jakosc = 0.1;

			cap >> image;
			imshow("window", image);

			if (start == true) {
				start = false;

				cvtColor(image, szareStare, COLOR_BGR2GRAY);
				goodFeaturesToTrack(szareStare, stare, rogi, jakosc, dystans, Mat(), 3, 3, false, 0.04);
			}else{
				image.copyTo(image2);
				cvtColor(image, szareNowe, COLOR_BGR2GRAY);
				goodFeaturesToTrack(szareNowe, nowe, rogi, jakosc, dystans, Mat(), 3, 3, false, 0.04);

				vector<uchar> status;
				vector<float> err;
				calcOpticalFlowPyrLK(szareStare, szareNowe, stare, nowe, status, err);

				size_t i, k;
				for (i = k = 0; i < nowe.size(); i++)
				{
					nowe[k++] = nowe[i];
					circle(image2, nowe[i], 3, Scalar(255, 0, 0), -1, 8);
				}
				nowe.resize(k);
				imshow("window2", image2);

				stare = nowe;
				szareNowe.copyTo(szareStare);
			}
			


		}
		catch (Exception e) {
			//cap.release();
			//cvDestroyAllWindows();
			//break;
		}

		if (waitKey(15) == 27) {
			cap.release();
			cvDestroyAllWindows();
			break;
		}
	}

	return 0;
}