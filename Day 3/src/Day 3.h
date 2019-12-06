#include <string>
#include "Wire.h"
#include "WireSegment.h"
#include "Point.h"
#include <vector>

int FindClosestIntersection(std::string const& input);
std::vector<Wire> GetWires(std::string const& input);
int FindDistanceFromPoint(Point central_point, std::list<WireIntersection>::value_type const& intersection);
int FindShortestDistance(std::list<int> const& distances);