#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>

#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

int robocza1;
int robocza2;
int robocza3;

double skala;
int sasiedzi;
int rozmiar;

void on_trackbar(int, void*)
{
	skala = (1.05+((double)robocza1/20));
	sasiedzi = robocza2+3;
	rozmiar = robocza3+10;
}

int main() {

	namedWindow("Suwaki", 4);
	createTrackbar("scaleFactor", "Suwaki", &robocza1, 8, on_trackbar);
	createTrackbar("minNeighbors", "Suwaki", &robocza2, 3, on_trackbar);
	createTrackbar("minSize", "Suwaki", &robocza3, 20, on_trackbar);

	skala = 1.1;
	sasiedzi = 3;
	rozmiar = 30;

	Mat image;
	Mat image2;
	Mat image3;
	Mat pierwsza;
	
	vector<Rect> twarze;
	vector<Rect> oczy;
	CascadeClassifier kaskadaTwarzy;
	CascadeClassifier kaskadaOczu;	

	int wersja =1;
	
	Point centrum;
	Rect Rec;
	Mat zapisana;
	Mat wstawiana;

	VideoCapture cap;
	cap.open(0);
	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);

	String twazeNazwa = "D:\\klatki\\haarcascade_frontalface_alt.xml";
	String oczyNazwa = "D:\\klatki\\haarcascade_eye_tree_eyeglasses.xml";

	if (!kaskadaTwarzy.load(twazeNazwa)) { return -1; };
	if (!kaskadaOczu.load(oczyNazwa)) { return -1; };

	while (1) {
		try {
			cap >> image;		
			imshow("window", image);
			image.copyTo(image3);

			cvtColor(image, image2, CV_BGR2GRAY);
			equalizeHist(image2, image2);

			kaskadaTwarzy.detectMultiScale(image2, twarze, skala, sasiedzi, 0 | CV_HAAR_SCALE_IMAGE, Size(rozmiar, 30));

			for (size_t i = 0; i < twarze.size(); i++)
			{
				Mat ROI = image2(twarze[i]);
				Mat Roi = image(twarze[i]);
				kaskadaOczu.detectMultiScale(ROI, oczy, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

				switch (wersja)
				{
				case 1:
					centrum = Point(twarze[i].x + twarze[i].width*0.5, twarze[i].y + twarze[i].height*0.5);
					ellipse(image3, centrum, Size(twarze[i].width*0.5, twarze[i].height*0.5), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);

					for (size_t j = 0; j < oczy.size(); j++)
					{
						centrum = Point(twarze[i].x + oczy[j].x + oczy[j].width*0.5, twarze[i].y + oczy[j].y + oczy[j].height*0.5);
						int promien = cvRound((oczy[j].width + oczy[j].height)*0.25);
						circle(image3, centrum, promien, Scalar(255, 0, 0), 4, 8, 0);
					}
					break;

				case 2:
					if (oczy.size() > 1) {
						Point p1(twarze[i].x + oczy[0].x + oczy[0].width*0.5, twarze[i].y + oczy[0].y + oczy[0].height*0.5);
						Point p2(twarze[i].x + oczy[1].x + oczy[1].width*0.5, twarze[i].y + oczy[1].y + oczy[1].height*0.5);
						if (p1.x > p2.x) {
							p1.x = p1.x + 50;
							p1.y = p1.y + 50;
							p2.x = p2.x - 50;
							p2.y = p2.y - 50;
						}
						else {
							p1.x = p1.x - 50;
							p1.y = p1.y - 50;
							p2.x = p2.x + 50;
							p2.y = p2.y + 50;
						}
						rectangle(image3, p1, p2, Scalar(0, 0, 0), -1);
					}
					break;

				case 3:
					GaussianBlur(Roi, Roi, CvSize(55, 55), 0);
					Rec = Rect(twarze[i].x, twarze[i].y, twarze[i].width, twarze[i].height);
					Roi.copyTo(image3(Rec));
					break;

				case 4:
					if (i == 0) {
						Roi.copyTo(zapisana);
					}
					else
					{
						resize(zapisana, wstawiana, CvSize(twarze[i].width, twarze[i].height), 0, 0, CV_INTER_LINEAR);
						Rec = Rect(twarze[i].x, twarze[i].y, twarze[i].width, twarze[i].height);
						wstawiana.copyTo(image3(Rec));
					}
					break;

				default:
					break;
				}
				
			}
			imshow("window2", image3);


		}
		catch (Exception e) {
			//cap.release();
			//cvDestroyAllWindows();
			//break;
		}

		int znak = waitKey(15);
		switch (znak)
		{
		case 27:
				cap.release();
				cvDestroyAllWindows();
				return 0;
		case 48:
			wersja = 0;
			break;
		case 49:
			wersja = 1;
			break;
		case 50:
			wersja = 2;
			break;
		case 51:
			wersja = 3;
			break;
		case 52:
			wersja = 4;
			break;
		default:
			break;
		}

	}

	return 0;
}