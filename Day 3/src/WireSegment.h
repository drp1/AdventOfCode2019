#pragma once
#include "Point.h"
#include <vector>

#ifndef _WireSegment_h_
#define _WireSegment_h_

class WireSegment
{
public:
	WireSegment(Point const& startPoint, Point const& endPoint);
	~WireSegment();
	bool IsVertical() const;
	bool IsHorizontal() const;
	bool Intersection(WireSegment const& other, Point& intersection) const;

	static bool Intersects(WireSegment const& wire_segment);
	bool operator==(WireSegment const& other) const;

private:
	Point startPoint, endPoint;
};

#endif