#include "WireSegment.h"

WireSegment::WireSegment(Point const& startPoint, Point const& endPoint)
	: startPoint(startPoint), endPoint(endPoint)
{
}

WireSegment::~WireSegment() = default;

bool WireSegment::Intersects(WireSegment const& wire_segment)
{
	// TODO
	return false;
}

bool WireSegment::operator==(WireSegment const& other) const
{
	return this->startPoint == other.startPoint && this->endPoint == other.endPoint;
}

