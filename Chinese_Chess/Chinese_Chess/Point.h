#pragma once
class Point
{
public:
	Point(int x = 0, int y = 0) :x(x), y(y) {

	}
	Point(const Point& point) :x(point.x), y(point.y) {

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

