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

	int numer = 1;
	bool nagrywanie=true;
	bool pierwsza=true;
	bool ruch = false;
	int tryb = 0;
	auto start = Time::now();

	string nazwa;
	stringstream ss;

	VideoCapture cap;
	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	int fps = 25;
	CvSize rozmiar;
	rozmiar.width = 640;
	rozmiar.height = 480;
	VideoWriter twozony("D:\\klatki\\nowy1.avi", CV_FOURCC('D', 'I', 'V', 'X'), fps, rozmiar, true);

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
				ruch = detekcja(stara, nowa);
				if (tryb == 0 && ruch == true) {
					tryb = 1;					
				}
				if (tryb == 1 && ruch == false) {
					tryb = 2;
					start = Time::now();
				}
				if (tryb == 2) {
					auto teraz = Time::now();
					fsec roznica = teraz - start;
					ms czas = std::chrono::duration_cast<ms>(roznica);
					int czas2 = czas.count();
					if (czas2 > 5000) {
						tryb = 3;
					}
				}

				if (nagrywanie == true) {
					if (tryb == 1 || tryb == 2) {
						circle(rys, Point(10, 10), 6, Scalar(0, 0, 255), -1, 8);
						time_t zegar = time(0);
						tm* czas = localtime(&zegar);
						char znaki[50];
						sprintf(znaki, "%d-%02d-%02d %02d:%02d:%02d", (czas->tm_year + 1900), (czas->tm_mon + 1), (czas->tm_mday), (czas->tm_hour), (czas->tm_min), (czas->tm_sec));
						String napis(znaki);
						putText(zapis, napis, Point(5, 15), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
						twozony.write(zapis);
					}
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

		int znak = waitKey(15);
		switch (znak)
		{
		case 27:
			cap.release();
			twozony.release();
			cvDestroyAllWindows();
			return 0;
		case 49: //1-spauzowanie nagrywania
			if (nagrywanie == true) {
				nagrywanie = false;
			}
			else {
				nagrywanie = true;
			}
			break;
		case 50: //2-przerwanie nagrania
			tryb = 3;
			break;
		case 51: //3-nowe nagranie
			numer++;
			twozony.release();
			nazwa = "D:\\klatki\\nowy";
			ss.str(std::string());
			ss << numer;
			nazwa += string(ss.str());
			nazwa += ".avi";
			twozony = VideoWriter(nazwa, CV_FOURCC('D', 'I', 'V', 'X'), fps, rozmiar, true);
			tryb = 0;
			pierwsza = true;
			break;
		default:
			break;
		}
	}

	return 0;
}