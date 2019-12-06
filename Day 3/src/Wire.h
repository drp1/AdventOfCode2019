#pragma once
#include <list>
#include <vector>
#include <string>
#include "WireSegment.h"



class Wire
{
public:
	Wire(std::string const& directions);
	Wire(std::vector<WireSegment> wireSegments) : segments(wireSegments)
	{	}
	~Wire();

	std::vector<WireSegment> const& Segments() const;

private:
	std::vector<WireSegment> segments;
};
