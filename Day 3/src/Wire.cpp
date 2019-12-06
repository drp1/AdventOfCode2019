#include "Wire.h"
#include <sstream>
#include "Point.h"

// ================== Wire
Wire::Wire(std::string const& directions)
{
	std::stringstream ss(directions);
	std::string direction;

	Point startPoint = Point(0,0);
	Point endPoint = startPoint;
	while(std::getline(ss, direction, ','))
	{
		int const magnitude = stoi(direction.substr(1, direction.size() - 1));
		switch(direction.at(0))
		{
		case 'U':
			endPoint = Point(startPoint.GetX(),  startPoint.GetY() + magnitude);
			break;
		case 'D':
			endPoint = Point(startPoint.GetX(), startPoint.GetY() - magnitude);
			break;
		case 'L':
			endPoint = Point(startPoint.GetX() - magnitude, startPoint.GetY());
			break;
		case 'R':
			endPoint = Point(startPoint.GetX() + magnitude, startPoint.GetY());
			break;
		default:
			// TODO
			break;
		}

		segments.push_back(WireSegment(startPoint, endPoint));
		startPoint = Point(endPoint);
	}
	
}

Wire::~Wire()
= default;

std::vector<WireSegment> const& Wire::Segments() const
{
	return segments;
}






WireIntersection::WireIntersection(WireSegment wire1_segment, WireSegment wire2_segment)
{
	// TODO
}


