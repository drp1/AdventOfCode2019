#include "Point.h"

Point::Point(int const x, int const y) : x(x), y(y)
{
}

bool Point::operator==(Point const& other) const
{
	return this->x == other.x && this->y == other.y;
}

int Point::GetX() const
{
	return x;
}

int Point::GetY() const
{
	return y;
}
