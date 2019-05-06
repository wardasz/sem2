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

int ilosc;
double jakosc;
double dystans;

bool zmiana;

void on_trackbar(int, void*)
{
	if (robocza1 > 10) {
		ilosc = robocza1;
	}
	else {
		ilosc = 10;
	}
	if (robocza2 = 0) {
		jakosc = (double)(robocza2/10);
	}
	else {
		jakosc = 0.1;
	}
	if (robocza3 > 10) {
		dystans = robocza3;
	}
	else {
		dystans = 10;
	}
	zmiana = true;
}

bool czyZaDaleko(Point2f p1, Point2f p2, int odleglosc) {
	return (abs(p1.x - p2.x) > odleglosc || abs(p1.y - p2.y) > odleglosc);
}


int main() {

	VideoCapture cap;
	Mat image;
	Mat image2;
	Mat staryGray;
	Mat nowyGray;
	vector<Point2f> rogi;
	vector<Point2f> sledzone;
	vector<Point2f> tmp;
	vector<uchar> status;
	vector<float> blendy;
	bool start = true;
	zmiana = false;

	namedWindow("Suwaki", 4);
	createTrackbar("maxCorners", "Suwaki", &robocza1, 100, on_trackbar);
	createTrackbar("qualityLevel,", "Suwaki", &robocza2, 10, on_trackbar);
	createTrackbar("minDistance", "Suwaki", &robocza3, 100, on_trackbar);

	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	ilosc = 30;
	jakosc = 0.1;
	dystans = 10;

	while (1) {
		try {
			
			cap >> image;
			image.copyTo(image2);
			imshow("window", image);

			if (start == true) {
				cvtColor(image, staryGray, COLOR_BGR2GRAY);
				tmp.clear();
				sledzone.clear();
				goodFeaturesToTrack(staryGray, tmp, ilosc, jakosc, dystans);
				for (int i = 0; i < tmp.size(); ++i) {
					sledzone.push_back(tmp[i]);
				}

				start = false;
			}else{
				cvtColor(image, nowyGray, COLOR_BGR2GRAY);
				if (sledzone.size() > 0) {
					calcOpticalFlowPyrLK(staryGray, nowyGray, sledzone, rogi, status, blendy);

				}
				
				int licznik = 0;
				for (int i = 0; i < status.size(); i++) {
					if (status[i] == false || czyZaDaleko(sledzone[licznik], rogi[licznik], 2) == false) {
						sledzone.erase(sledzone.begin() + licznik);
						rogi.erase(rogi.begin() + licznik);
					}
					else {
						licznik++;
					}
				}				

				for (int i = 0; i < sledzone.size(); ++i) {
					circle(image2, sledzone[i], 3, Scalar(0, 0, 255), -1, 8);
					line(image2, sledzone[i], rogi[i], Scalar(0, 0, 255));
				}

				if (sledzone.size() < 10 || zmiana == true) {
					nowyGray.copyTo(staryGray);
					tmp.clear();
					sledzone.clear();
					goodFeaturesToTrack(staryGray, tmp, ilosc, jakosc, dystans);
					for (int i = 0; i < tmp.size(); ++i) {
						sledzone.push_back(tmp[i]);
					}
					zmiana = false;
				}
				
				rogi.clear();
				status.clear();

				imshow("window2", image2);
			}
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