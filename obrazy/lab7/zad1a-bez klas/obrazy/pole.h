#pragma once
class pole
{
public:
	pole();
	pole(cv::Point);
	~pole();
	cv::Point dajKoordynaty();
	void ustawKoordynaty(cv::Point);

private:
	cv::Point koordynaty;
};

