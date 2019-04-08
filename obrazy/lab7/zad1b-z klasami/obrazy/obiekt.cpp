#include "obiekt.h"

#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iomanip>
#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

class obiekt {

	private: Point wspolzendne;



	public: obiekt::obiekt(Point p)
	{
		wspolzendne = p;
	}


	obiekt::~obiekt()
	{
	}
}
