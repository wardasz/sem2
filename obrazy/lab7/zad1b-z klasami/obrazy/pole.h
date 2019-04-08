#pragma once
class pole
{
public:
	pole();
	pole(int x, int y);
	~pole();
	void ustawX(int);
	void ustawY(int);
	int dajX();
	int dajY();

private:
	int X;
	int Y;
};
