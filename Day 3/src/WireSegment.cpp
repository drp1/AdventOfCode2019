#include "WireSegment.h"
#include <algorithm>

WireSegment::WireSegment(Point const& startPoint, Point const& endPoint)
	: startPoint(startPoint), endPoint(endPoint)
{
}

WireSegment::~WireSegment() = default;

bool WireSegment::IsVertical() const
{
	return startPoint.GetY() - endPoint.GetY() != 0;
}

bool WireSegment::IsHorizontal() const
{
	return startPoint.GetX() - endPoint.GetX() != 0;
}

bool WireSegment::Intersection(WireSegment const& other, Point& intersection) const
{
	auto const x1 = this->startPoint.GetX();
	auto const x2 = this->endPoint.GetX();
	auto const x3 = other.startPoint.GetX();
	auto const x4 = other.endPoint.GetX();
	auto const y1 = this->startPoint.GetY();
	auto const y2 = this->endPoint.GetY();
	auto const y3 = other.startPoint.GetY();
	auto const y4 = other.endPoint.GetY();
	
	if (std::min(x1, x2) > std::max(x3, x4))
		return false;
	if (std::min(y1, y2) > std::max(y3, y4))
		return false;
	
	if(this->IsVertical() && other.IsHorizontal())
	{
		if (std::max(y1, y2) <= y3 || std::min(y1, y2) >= y3
			|| std::max(x3, x4) <= x1 || std::min(x3, x4) >= x1)
			return false;
		intersection.SetXY(x1, y3);
	}
	else if (this->IsHorizontal() && other.IsVertical())
	{
		if (std::max(x1, x2) <= x3 || std::min(x1, x2) >= x3 
			|| std::max(y3, y4) <= y1 || std::min(y3, y4) >= y1)
			return false;
		intersection.SetXY(x3, y1);
	}
	else
	{
		return false; // Parallel lines
	}

	return true;
}


bool WireSegment::Intersects(WireSegment const& wire_segment)
{
	// TODO
	return false;
}

bool WireSegment::operator==(WireSegment const& other) const
{
	return this->startPoint == other.startPoint && this->endPoint == other.endPoint;
}

