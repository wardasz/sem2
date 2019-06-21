#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>

#include<iostream>
#include<conio.h>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "Panel Sterowania"

using namespace cv;
using namespace std;

int robocza1;
int robocza2;
int robocza3;
int robocza4;

double skala;
int sasiedzi;
int rozmiarMin;
int rozmiarMax;

void on_trackbar(int, void*)
{
	skala = (1.05 + ((double)robocza1 / 20));
	sasiedzi = robocza2 + 3;
	rozmiarMin = robocza3 + 10;
	rozmiarMax = robocza4 + 150;

}

int main() {

	cv::Mat frame = cv::Mat(330, 250, CV_8UC3);

	cvui::init(WINDOW_NAME);

	bool wybrano = false;
	
	VideoCapture cap;	

	cv::namedWindow("Suwaki", 4);
	cv::createTrackbar("scaleFactor", "Suwaki", &robocza1, 8, on_trackbar);
	cv::createTrackbar("minNeighbors", "Suwaki", &robocza2, 3, on_trackbar);
	cv::createTrackbar("minSize", "Suwaki", &robocza3, 50, on_trackbar);
	cv::createTrackbar("maxSize", "Suwaki", &robocza4, 150, on_trackbar);

	skala = 1.1;
	sasiedzi = 3;
	rozmiarMin = 10;
	rozmiarMax = 250;

	Mat zrodlo;
	Mat szara;
	Mat rysunki;
	Mat wynik;
	
	vector<Rect> twarze;
	CascadeClassifier kaskadaTwarzy;

	int numer = 1;
	int numerZrzutu = 1;
	int tryb = 0;  //0-nic, 1-prostok¹t, 2-blur, 3-podmiana twarzy
	bool zapis = false;
	int zrzuty = 0;

	string nazwa;
	stringstream ss;
	int fps = 15;
	CvSize rozmiar;
	rozmiar.width = 640;
	rozmiar.height = 480;
	VideoWriter twozony;

	Mat obszarObraz;
	Rect obszarKordy;
	Mat twaz;
	Point centrum;
	Mat zapisana;
	Mat wstawiana;
	Point pg;
	Point ld;

	string sciezkaOdczytu;
	string sciezkaZapisu;
	string sciezkaTwazy;
	string tmp;

	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(100);

	cv::namedWindow("window", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("window2", CV_WINDOW_AUTOSIZE);

	String twazeNazwa = "D:\\klatki\\haarcascade_frontalface_alt.xml";

	if (!kaskadaTwarzy.load(twazeNazwa)) { return -1; };

	while (1) {
		try {
			frame = cv::Scalar(49, 52, 49);
			if (cvui::button(frame, 20, 10, "Przetwarzaj obraz z kamery")) {
				cap.open(0);
				double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
				double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
				wybrano = true;
			}

			if (cvui::button(frame, 20, 50, "Przetwarzaj obraz z dysku")) {
				cout << "Podaj nazwê pliku który chcesz otworzyæ: ";
				cin >> tmp;
				sciezkaOdczytu = "D:\\klatki\\";
				ss.str(std::string());
				ss << tmp;
				sciezkaOdczytu += string(ss.str());
				sciezkaOdczytu += ".avi";
				cap = cv::VideoCapture(sciezkaOdczytu);
				wybrano = true;
			}

			if (cvui::button(frame, 20, 90, "Wylacz maskowanie")) {
				tryb = 0;
			}

			if (cvui::button(frame, 20, 130, "Dodaj prostok¹t")) {
				tryb = 1;
			}

			if (cvui::button(frame, 20, 170, "Dodaj rozmycie")) {
				tryb = 2;
			}

			if (cvui::button(frame, 20, 210, "Podstaw obraz")) {
				tryb = 3;				
				cout << "Podaj nazwê pliku który chcesz wstawiæ: ";
				cin >> tmp;
				sciezkaTwazy = "D:\\klatki\\";
				ss.str(std::string());
				ss << tmp;
				sciezkaTwazy += string(ss.str());
				sciezkaTwazy += ".jpg";
				twaz = imread(sciezkaTwazy, CV_LOAD_IMAGE_UNCHANGED);
			}

			if (cvui::button(frame, 20, 250, "Wlacz/wylacz nagrywanie")) {
				if (zapis == false) {
					zapis = true;
					sciezkaZapisu = "D:\\klatki\\nowy";
					ss.str(std::string());
					ss << numer;
					sciezkaZapisu += string(ss.str());
					sciezkaZapisu += ".avi";
					twozony = VideoWriter(sciezkaZapisu, CV_FOURCC('D', 'I', 'V', 'X'), fps, rozmiar, true);
				}
				else {
					zapis = false;
					numer++;
					twozony.release();
				}
			}

			if (cvui::button(frame, 20, 290, "Zapisz twarze")) {
				cout << "Podaj liczbê klatek dla których chcesz zapisaæ zrzuty twarzy: ";
				cin >> zrzuty;
			}

			cvui::imshow(WINDOW_NAME, frame);

			if (wybrano == true) {
				cap >> zrodlo;
				resize(zrodlo, zrodlo, CvSize(640, 480), 0, 0, CV_INTER_LINEAR);
				zrodlo.copyTo(rysunki);
				zrodlo.copyTo(wynik);

				cvtColor(zrodlo, szara, CV_BGR2GRAY);
				equalizeHist(szara, szara);

				kaskadaTwarzy.detectMultiScale(szara, twarze, skala, sasiedzi, 0 | CV_HAAR_SCALE_IMAGE, Size(rozmiarMin, rozmiarMin), Size(rozmiarMax, rozmiarMax));

				for (size_t i = 0; i < twarze.size(); i++)
				{
					obszarObraz = zrodlo(twarze[i]);
					obszarKordy = Rect(twarze[i].x, twarze[i].y, twarze[i].width, twarze[i].height);
					centrum = Point(twarze[i].x + twarze[i].width*0.5, twarze[i].y + twarze[i].height*0.5);
					ellipse(rysunki, centrum, Size(twarze[i].width*0.5, twarze[i].height*0.5), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);

					switch (tryb)
					{
					case 1:  //czarny prostok¹t
						pg = Point(twarze[i].x, twarze[i].y+(twarze[i].height*0.2));
						ld = Point(twarze[i].x+ twarze[i].width, twarze[i].y + (twarze[i].height * 0.6));
						rectangle(wynik, pg, ld, Scalar(0, 0, 0), -1);					
						break;

					case 2:  //blur
						GaussianBlur(obszarObraz, obszarObraz, CvSize(55, 55), 0);						
						obszarObraz.copyTo(wynik(obszarKordy));
						break;

					case 3:  //podstawienie twarzy
						twaz.copyTo(wstawiana);
						resize(wstawiana, wstawiana, CvSize(twarze[i].width, twarze[i].height), 0, 0, CV_INTER_LINEAR);
						wstawiana.copyTo(wynik(obszarKordy));					
						break;

					default:
						break;
					}			
					if (zrzuty > 0) {  //robienei zrzutów
						string sciezka = "D:\\klatki\\zrzut";
						stringstream ss;
						ss << numerZrzutu;
						sciezka += string(ss.str());
						sciezka += ".jpg";
						bool bSuccess = imwrite(sciezka, wynik(obszarKordy), compression_params);
						numerZrzutu++;
					}
				}
				if (zapis == true) {
					circle(rysunki, Point(10, 10), 6, Scalar(0, 0, 255), -1, 8);
					twozony.write(wynik);
				}
				if (zrzuty > 0) {
					zrzuty--;
				}

				cv::imshow("window", rysunki);
				cv::imshow("window2", wynik);
			}

		}
		catch (Exception e) {
			//if (zapis == true) {
			//	twozony.release();
			//}
			//cap.release();
			//cvDestroyAllWindows();
			//break;
		}
		if (waitKey(15) == 27) {
			if (zapis == true) {
				twozony.release();
			}
			cap.release();
			cvDestroyAllWindows();
			break;
		}
	}
	return 0;
}