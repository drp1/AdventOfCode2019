#pragma once
#include "Point.h"

#ifndef _WireSegment_h_
#define _WireSegment_h_

class WireSegment
{
public:
	WireSegment(Point const& startPoint, Point const& endPoint);
	~WireSegment();

	static bool Intersects(WireSegment const& wire_segment);
	bool operator==(WireSegment const& other) const;

private:
	Point startPoint, endPoint;
};

#endif