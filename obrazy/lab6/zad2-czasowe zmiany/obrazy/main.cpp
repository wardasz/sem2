#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include <chrono>
#include <ctime> 

#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

int hg1=105;
int hd1=22;
int sg1=184;
int sd1=18;
int vg1=255;
int vd1=75;

int hg2=86;
int hd2=16;
int sg2=50;
int sd2=25;
int vg2=255;
int vd2=227;

int hg3=0;
int hd3=0;
int sg3=0;
int sd3=0;
int vg3=0;
int vd3=0;

int hg;
int hd;
int sg;
int sd;
int vg;
int vd;


int main() {

	Mat image;
	Mat image2;
	Mat image3;
	Mat image4;
	Mat image5;
	Mat image6;
	Mat image7;
	VideoCapture cap;
	RNG rng(12345);

	cap.open(0);

	namedWindow("window", CV_WINDOW_AUTOSIZE);
	namedWindow("window2", CV_WINDOW_AUTOSIZE);
	namedWindow("window3", CV_WINDOW_AUTOSIZE);
	namedWindow("window4", CV_WINDOW_AUTOSIZE);
	namedWindow("window5", CV_WINDOW_AUTOSIZE);
	namedWindow("window6", CV_WINDOW_AUTOSIZE);

	double dWidth = cap.set(CV_CAP_PROP_FRAME_WIDTH, 384);
	double dHeight = cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

	int licznik = 1;
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;
	auto start = Time::now();

	while (1) {
		try {
			auto teraz = Time::now();
			fsec roznica = teraz - start;
			ms czas = std::chrono::duration_cast<ms>(roznica);
			int czas2 = czas.count();
			if (czas2 > 5000) {
				licznik=licznik+1;
				if (licznik > 3) licznik = 1;
				start = Time::now();
			}
			switch (licznik) {
			case 1:
				hd = hd1;
				hg = hg1;
				sd = sd1;
				sg = sg1;
				vd = vd1;
				vg = vg1;
				break;
			case 2:
				hd = hd2;
				hg = hg2;
				sd = sd2;
				sg = sg2;
				vd = vd2;
				vg = vg2;
				break;
			case 3:
				hd = hd3;
				hg = hg3;
				sd = sd3;
				sg = sg3;
				vd = vd3;
				vg = vg3;
				break;
			}

			cap >> image;
			imshow("window", image);

			cvtColor(image, image2, CV_BGR2HSV);			

			//ustalanie wartoœci
			inRange(image2, Scalar(hd, sd, vd), Scalar(hg, sg, vg), image3);
			imshow("window2", image3);

			Mat element1 = getStructuringElement(cv::MORPH_CROSS,
				cv::Size(2 * 3 + 1, 2 * 3 + 1),
				cv::Point(3, 3));
			Mat element2 = getStructuringElement(cv::MORPH_CROSS,
				cv::Size(2 * 8 + 1, 2 * 8 + 1),
				cv::Point(8, 8));

			erode(image3, image4, element1);
			erode(image4, image4, element1);
			imshow("window3", image4);		
			dilate(image4, image5, element2);
			dilate(image5, image5, element2);
			imshow("window4", image5);

			vector<vector<Point>> kontury;
			vector<Vec4i> hier;
			findContours(image5, kontury, hier, RETR_TREE, CHAIN_APPROX_SIMPLE);
			vector<Moments> mu(kontury.size());
			for (int i = 0; i < kontury.size(); i++)
			{
				mu[i] = moments(kontury[i], false);
			}
			vector<Point2f> mc(kontury.size());
			for (int i = 0; i < kontury.size(); i++)
			{
				mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
			}

			Mat drawing = Mat::zeros(image.size(), CV_8UC3);
			for (int i = 0; i < kontury.size(); i++)
			{
				Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
				drawContours(drawing, kontury, i, color, 2, 8, hier, 0, Point());
				circle(drawing, mc[i], 4, color, -1, 8, 0);
			}
			imshow("window5", drawing);

			image.copyTo(image7);
			Moments m = moments(image5, true);
			Point p(m.m10 / m.m00, m.m01 / m.m00);

			circle(image7, p, 3, Scalar(0, 0, 255));
			String x = to_string(m.m10 / m.m00);
			String y = to_string(m.m01 / m.m00);
			String text = "Wsp: " + x + "," + y;
			putText(image7, text, p, FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
			imshow("window6", image7);
				
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