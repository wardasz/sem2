#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>

#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;


int main() {
	bool pierwsza = true;

	Mat stara;
	Mat nowa;
	Mat nowaGray;
	Mat staraGray;
	Mat robocza;
	Mat rysunki;

	VideoCapture cap;
	cap.open(0);
	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);

	while (1) {
		try {
			if (pierwsza == true) {
				cap >> stara;
				cvtColor(stara, staraGray, CV_BGR2GRAY);
				pierwsza == false;
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
				threshold(robocza, robocza, 100, 255, CV_THRESH_BINARY);

				vector<vector<Point>> kontury;
				vector<Vec4i> hier;
				findContours(robocza, kontury, hier, RETR_TREE, CHAIN_APPROX_SIMPLE);
				int najwiekszy = 0;
				for (int i = 0; i < kontury.size(); i++)
				{
					if (contourArea(kontury[i]) > contourArea(kontury[najwiekszy])) {
						najwiekszy = i;
					}
				}





				imshow("window2", rysunki);
				nowa.copyTo(stara);
				nowaGray.copyTo(staraGray);
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