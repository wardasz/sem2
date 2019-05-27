#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>

#include<chrono>
#include<iomanip>
#include<ctime>  

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace cv;
using namespace std;

bool detekcja(Mat stara, Mat nowa) {

	Mat staraSzara;
	Mat nowaSzara;
	cvtColor(stara, staraSzara, CV_BGR2GRAY);
	cvtColor(nowa, nowaSzara, CV_BGR2GRAY);

	Mat robocza;
	absdiff(nowaSzara, staraSzara, robocza);

	CvSize rozmiar;
	rozmiar.width = (10 * 2) + 1;
	rozmiar.height = (10 * 2) + 1;
	GaussianBlur(robocza, robocza, rozmiar, 0);
	threshold(robocza, robocza, 80, 255, CV_THRESH_BINARY);

	vector<vector<Point>> kontury;
	vector<Vec4i> hier;
	findContours(robocza, kontury, hier, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//findContours(robocza, kontury, hier, RETR_TREE, CV_RETR_EXTERNAL);
	if (kontury.size() > 0) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;

	Mat stara;
	Mat nowa;
	Mat rys;
	Mat zapis;

	bool pierwsza=true;

	VideoCapture cap;
	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	int fps = 25;
	CvSize rozmiar;
	rozmiar.width = 640;
	rozmiar.height = 480;
	VideoWriter twozony("D:\\klatki\\nowy.avi", CV_FOURCC('D', 'I', 'V', 'X'), fps, rozmiar, true);

	while (1) {
		try {
			if (pierwsza==true) {
				cap >> stara;
				imshow("window", stara);
				pierwsza = false;
			}else{
				cap >> nowa;
				nowa.copyTo(rys);
				nowa.copyTo(zapis);
				if (detekcja(stara, nowa) == true) {
					circle(rys, Point(10, 10), 6, Scalar(0, 0, 255), -1, 8);

					putText(zapis, napis, Point(5, 15), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
					twozony.write(zapis);
				}
				imshow("window", rys);
				nowa.copyTo(stara);
			}

			
		}
		catch (Exception e) {
			cap.release();
			twozony.release();
			cvDestroyAllWindows();
			break;
		}

		if (waitKey(15) == 27) {
			cap.release();
			twozony.release();
			cvDestroyAllWindows();
			break;
		}
	}

	return 0;
}