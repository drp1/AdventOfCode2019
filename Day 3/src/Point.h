
#ifndef _Point_h_
#define _Point_h_

class Point
{
public:
	Point(int const x, int const y) : x(x), y(y)
	{}

	bool operator==(Point const& other) const
	{
		return this->x == other.x && this->y == other.y;
	}

	int GetX() const
	{
		return x;
	}

	int GetY() const
	{
		return y;
	}

	void SetX(int const x)
	{
		this->x = x;
	}

	void SetY(int const y)
	{
		this->y = y;
	}

	void SetXY(int const x, int const y)
	{
		SetX(x);
		SetY(y);
	}
	
private:
	int x, y;
};










#endif