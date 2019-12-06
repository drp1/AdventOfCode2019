#include <string>
#include "Wire.h"
#include "WireSegment.h"
#include "Point.h"
#include <vector>

int FindClosestIntersection(std::string const& input);
std::list<Point> FindIntersections(Wire const& wire1, Wire const& wire2);
std::vector<Wire> GetWires(std::string const& input);
int FindDistanceFromPoint(Point const& central_point, Point const& intersection);
int FindShortestDistance(std::list<int> const& distances);