#pragma once
#include <list>


class WireIntersection;
class WireSegment;

class Wire
{
public:
	Wire();
	~Wire();

	std::list<WireSegment>& Segments() const;

	class Test
	{
		
	};
};

class WireIntersection
{
public:
	WireIntersection(WireSegment wire1_segment, WireSegment wire2_segment);
};

class WireSegment
{
public:
	bool Intersects(WireSegment const& wire_segment);
};

class Point
{
public:
	Point(int x, int y);
};