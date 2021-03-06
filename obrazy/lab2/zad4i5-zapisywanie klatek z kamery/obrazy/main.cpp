#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>

#include <chrono>
#include <ctime>  

using namespace cv;
using namespace std;

int main() {
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;

	int ile = 0;
	int opuznienie = 0;

	printf("Ile klatek chcesz zapisa�: ");
	cin >> ile;
	printf("Jakie du�e ma by� op�nienie przed rozpocz�ciem zapisu (w milisekundach): ");
	cin >> opuznienie;

	Mat image;
	VideoCapture cap;

	cap.open(0);
	auto start = Time::now();

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	int numer = 0;
	while (1) {
		try {
			
			cap >> image;

			vector<int> compression_params;
			compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
			compression_params.push_back(100);

			

			auto teraz = Time::now();
			fsec roznica = teraz - start;
			ms czas = std::chrono::duration_cast<ms>(roznica);
			int czas2 = czas.count();
			cout << czas2 << "\n";
			if (czas2 > opuznienie) {
				numer=numer+1;
				if (numer <= ile) {

					string sciezka = "D:\\klatki\\obrazek";
					stringstream ss;
					ss << numer;
					sciezka += string(ss.str());
					sciezka += ".jpg";

					bool bSuccess = imwrite(sciezka, image, compression_params);
					cout << "Zapisuje obraz nr" << numer << "\n";
				}
				else {
					cap.release();
					break;
				}
			}
			
		}
		catch (Exception e) {
			cap.open(1);
		}

		if (waitKey(15) == 27) {
			cap.release();
			break;
		}
	}

	return 0;
}