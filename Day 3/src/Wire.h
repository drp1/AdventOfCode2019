#pragma once
#include <list>
#include <vector>
#include <string>
#include "WireSegment.h"

class WireIntersection;
class WireSegment;

class Wire
{
public:
	Wire(std::string const& directions);
	~Wire();

	std::vector<WireSegment> const& Segments() const;

private:
	std::vector<WireSegment> segments;
};

class WireIntersection
{
public:
	WireIntersection(WireSegment wire1_segment, WireSegment wire2_segment);
};


class WireVector
{
public:
	
	WireVector(std::string const& direction);
};