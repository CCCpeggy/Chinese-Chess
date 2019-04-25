#pragma once
class Point
{
public:
	Point(int = 0, int = 0) :x(x), y(y) {

	}
	char x;
	char y;
	Point Point::operator+(Point& p)
	{
		return Point(x + p.x, y + p.y);
	}
	Point Point::operator*(int n)
	{
		return Point(x * n, y * n);
	}
	bool Point::operator==(Point& p)
	{
		return x == p.x && y==p.y;
	}
};

