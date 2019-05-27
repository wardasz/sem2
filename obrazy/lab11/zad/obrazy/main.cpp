#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/video/tracking.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/video/background_segm.hpp>

#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

bool czyZaDaleko(Point2f p1, Point2f p2, int odleglosc) {
	return (abs(p1.x - p2.x) > odleglosc || abs(p1.y - p2.y) > odleglosc);
}

int main() {
	Mat stara;
	Mat nowa;
	Mat nowaGray;
	Mat staraGray;
	Mat robocza;
	Mat rysunki;

	vector<Point2f> rogi;
	vector<Point2f> sledzone;
	vector<Point2f> tmp;
	vector<uchar> status;
	vector<float> blendy;

	Ptr<BackgroundSubtractorMOG2> mog; //MOG2 Background subtractor
	mog = createBackgroundSubtractorMOG2(500, 16, true);


	Mat front;
	Mat tlo;

	VideoCapture cap;
	cap.open(0);
	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 384);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

	bool pierwsza = true;
	int wersja = 1;
	bool detekcja = true;
	bool kontynuacja = true;

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);

	while (1) {
		try {
			if (kontynuacja == true) {
				if (detekcja == true) {
					if (wersja == 1) { //ró¿nica jasnoœci
						if (pierwsza == true) {
							cap >> stara;
							cvtColor(stara, staraGray, CV_BGR2GRAY);
							pierwsza = false;
						}
						else {
							cap >> nowa;
							nowa.copyTo(rysunki);
							imshow("window", nowa);
							cvtColor(nowa, nowaGray, CV_BGR2GRAY);

							absdiff(nowaGray, staraGray, robocza);
							CvSize rozmiar;
							rozmiar.width = (10 * 2) + 1;
							rozmiar.height = (10 * 2) + 1;
							GaussianBlur(robocza, robocza, rozmiar, 0);
							threshold(robocza, robocza, 80, 255, CV_THRESH_BINARY);

							vector<vector<Point>> kontury;
							vector<Vec4i> hier;
							findContours(robocza, kontury, hier, RETR_TREE, CHAIN_APPROX_SIMPLE);
							if (kontury.size() > 0) {
								int najwiekszy = 0;
								vector<Point> max = kontury[0];
								for (int i = 0; i < kontury.size(); i++)
								{
									if (contourArea(kontury[i]) > contourArea(kontury[najwiekszy])) {
										najwiekszy = i;
										max = kontury[i];
									}
								}
								drawContours(rysunki, kontury, najwiekszy, Scalar(240, 1, 1), 2, 8, hier, 0, Point());
								rectangle(rysunki, boundingRect(max), Scalar(1, 240, 1), 2, 8, 0);
								vector<Point> otoczka;
								convexHull(max, otoczka, false);
								for (int i = 0; i < otoczka.size(); i++)
								{
									Point a = otoczka[i];
									int j = i + 1;
									if (j == otoczka.size()) j = 0;
									Point b = otoczka[j];
									line(rysunki, a, b, Scalar(1, 1, 240), 2, 8, 0);
								}
								Moments centrum;
								centrum = moments(max, false);
								Point p(centrum.m10 / centrum.m00, centrum.m01 / centrum.m00);
								String x = to_string(centrum.m10 / centrum.m00);
								String y = to_string(centrum.m01 / centrum.m00);
								String tekst = "Wsp: " + x;
								tekst = tekst + "," + y;
								putText(rysunki, tekst, p, FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
								circle(rysunki, p, 2, Scalar(0, 0, 0), 3);

							}

							imshow("window2", rysunki);
							nowa.copyTo(stara);
							nowaGray.copyTo(staraGray);
						}
					}else{
						if (wersja == 2) { //optical flow
							if (pierwsza == true) {
								cap >> stara;
								cvtColor(stara, staraGray, COLOR_BGR2GRAY);
								tmp.clear();
								sledzone.clear();
								goodFeaturesToTrack(staraGray, tmp, 30, 0.1, 10);
								for (int i = 0; i < tmp.size(); ++i) {
									sledzone.push_back(tmp[i]);
								}

								pierwsza = false;
							}
							else {
								cap >> nowa;
								nowa.copyTo(rysunki);
								imshow("window", nowa);
								cvtColor(nowa, nowaGray, COLOR_BGR2GRAY);

								if (sledzone.size() > 0) {
									calcOpticalFlowPyrLK(staraGray, nowaGray, sledzone, rogi, status, blendy);
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
									circle(rysunki, sledzone[i], 3, Scalar(0, 0, 255), -1, 8);
									line(rysunki, sledzone[i], rogi[i], Scalar(0, 0, 255));
								}

								if (sledzone.size() < 10) {
									nowaGray.copyTo(staraGray);
									tmp.clear();
									sledzone.clear();
									goodFeaturesToTrack(staraGray, tmp, 30, 0.1, 10);
									for (int i = 0; i < tmp.size(); ++i) {
										sledzone.push_back(tmp[i]);
									}
								}

								rogi.clear();
								status.clear();

								imshow("window2", rysunki);
							}
						}
						else  //gausiañski mix
						{
							cap >> nowa;
							nowa.copyTo(rysunki);
							imshow("window", nowa);
							mog->apply(nowa, front);
							mog->getBackgroundImage(tlo);

							vector<vector<Point>> kontury2;
							vector<Vec4i> hier2;
							findContours(front, kontury2, hier2, RETR_TREE, CHAIN_APPROX_SIMPLE);
							vector<Moments> mu2(kontury2.size());
							for (int i = 0; i < kontury2.size(); i++)
							{
								mu2[i] = moments(kontury2[i], false);
							}
							vector<Point2f> mc2(kontury2.size());
							for (int i = 0; i < kontury2.size(); i++)
							{
								mc2[i] = Point2f(mu2[i].m10 / mu2[i].m00, mu2[i].m01 / mu2[i].m00);
							}

							for (int i = 0; i < kontury2.size(); i++)
							{
								Scalar color = Scalar(0, 0, 255);
								drawContours(rysunki, kontury2, i, color, 2, 8, hier2, 0, Point());
								circle(rysunki, mc2[i], 4, color, -1, 8, 0);
							}
							imshow("window2", rysunki);
						}
						}
				}else {
					cap >> rysunki;
					imshow("window", rysunki);
					imshow("window2", rysunki);
				}			
			}
		}
		catch (Exception e) {
			cap.release();
			cvDestroyAllWindows();
			break;
		}

		int znak = waitKey(15);
		switch (znak)
		{
		case 27:
			cap.release();
			cvDestroyAllWindows();
			return 0;
		case 49:
			wersja = 1;
			pierwsza = true;
			break;
		case 50:
			wersja = 2;
			pierwsza = true;
			break;
		case 51:
			wersja = 3;
			pierwsza = true;
			break;
		case 52:
			if (detekcja == true) {
				detekcja = false;
			}else {
				detekcja = true;
			}
			break;
		case 53:
			if (kontynuacja == true) {
				kontynuacja = false;
			}
			else {
				kontynuacja = true;
			}
			break;
		default:
			break;
		}
		
	}

return 0;
}