#include "pole.h"

#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iomanip>

#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

pole::pole()
{
}

pole::pole(cv::Point p)
{
	koordynaty = p;
}
pole::~pole()
{
}

cv::Point pole::dajKoordynaty() {
	return koordynaty;
}

void pole::ustawKoordynaty(cv::Point p) {
	koordynaty=p;
}
