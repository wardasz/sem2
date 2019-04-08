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

pole::pole(int x, int y)
{
	X = x;
	Y = y;
}
pole::~pole()
{
}

void pole::ustawX(int x) {
	pole::X = x;
}

void pole::ustawY(int y) {
	pole::Y = y;
}

int pole::dajX() {
	return pole::X;
}

int pole::dajY() {
	return pole::Y;
}
