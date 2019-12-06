#include "Day 3.h"
#include <list>

#include "gtest/gtest.h"

using namespace std;

TEST(Day3TestSuite, ExampleInput1Test)
{
	string const testInput = "R8,U5,L5,D3\nU7,R6,D4,L4";
	auto const expectedDistance = 6;
	EXPECT_EQ(expectedDistance, FindClosestIntersection(testInput));
}

TEST(Day3TestSuite, ExampleInput2Test)
{
	string const testInput = "R75,D30,R83,U83,L12,D49,R71,U7,L72\nU62,R66,U55,R34,D71,R55,D58,R83";
	auto const expectedDistance = 159;
	EXPECT_EQ(expectedDistance, FindClosestIntersection(testInput));
}

TEST(Day3TestSuite, ExampleInput3Test)
{
	string const testInput = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51\nU98,R91,D20,R16,D67,R40,U7,R15,U6,R7";
	auto const expectedDistance = 135;
	EXPECT_EQ(expectedDistance, FindClosestIntersection(testInput));
}

TEST(Day3TestSuite, GetWires_Should_Return_Wires)
{
	string const testInput = "R8,U5,L5,D3\nU7,R6,D4,L4";
	auto wires = GetWires(testInput);

	EXPECT_EQ(wires.size(), 2);

	int const expectedNumWires = 2;
	int const expectedNumWireSegments = 4;

	WireSegment expectedWires[expectedNumWires][expectedNumWireSegments] = {
		{
			WireSegment(Point(0, 0), Point(8, 0)),
			WireSegment(Point(8,0), Point(8,5)),
			WireSegment(Point(8,5), Point(3,5)),
			WireSegment(Point(3,5), Point(3,2))
		},
		{
			WireSegment(Point(0,0), Point(0,7)),
			WireSegment(Point(0,7), Point(6,7)),
			WireSegment(Point(6,7), Point(6,3)),
			WireSegment(Point(6,3), Point(2,3)),
		}
	};

	for (int wireIndex = 0; wireIndex < expectedNumWires; wireIndex++)
	{
		for (int segmentIndex = 0; segmentIndex < expectedNumWireSegments; segmentIndex++)
		{
			EXPECT_EQ(wires[wireIndex].Segments()[segmentIndex], expectedWires[wireIndex][segmentIndex]);
		}
	}
}


TEST(Day3TestSuite, Should_Find_Intersections)
{
	int const numIntersections = 2;
	Point expectedIntersections[numIntersections] = {
		Point(3,3),
		Point(6, 5)
	};

	int const expectedNumWires = 2;
	int const expectedNumWireSegments = 4;

	vector<WireSegment> segments1 = {
				WireSegment(Point(0, 0), Point(8, 0)),
				WireSegment(Point(8,0), Point(8,5)),
				WireSegment(Point(8,5), Point(3,5)),
				WireSegment(Point(3,5), Point(3,2))
	};

	auto wire1 = Wire(segments1);

	vector<WireSegment>	segments2{
	 WireSegment(Point(0,0), Point(0,7)),
	 WireSegment(Point(0,7), Point(6,7)),
	 WireSegment(Point(6,7), Point(6,3)),
	 WireSegment(Point(6,3), Point(2,3)),
	};

	auto wire2 = Wire(segments2);

	Wire expectedWires[expectedNumWires] = {
		wire1,
		wire2
	};

	auto actualIntersections = FindIntersections(expectedWires[0], expectedWires[1]);

	EXPECT_EQ(actualIntersections.size(), numIntersections);
	
	bool foundSegment = false;

	for (auto& expectedIntersection : expectedIntersections)
	{
		foundSegment = false;
		for (auto& actualIntersection : actualIntersections)
		{
			if (expectedIntersection == actualIntersection)
			{
				foundSegment = true;
			}
		}
		EXPECT_TRUE(foundSegment);
	}
}



list<Point> FindIntersections(Wire const& wire1, Wire const& wire2)
{
	list<Point> intersections;
	for (auto& wire1Segment : wire1.Segments())
	{
		for (auto& wire2Segment : wire2.Segments())
		{
			Point intersection = Point(0, 0);
			if (wire1Segment.Intersection(wire2Segment, intersection))
			{
				intersections.push_back(intersection);
			}
		}

	}
	return intersections;
}

list<int> FindDistancesFromPoint(Point const& centralPoint, list<Point> const& intersections)
{
	list<int> distances;
	for (auto& intersection : intersections)
	{
		auto distance = FindDistanceFromPoint(centralPoint, intersection);
		distances.push_back(distance);
	}
	return distances;
}

std::vector<Wire> GetWires(std::string const& input)
{
	std::vector<Wire> wires;
	std::stringstream ss(input);
	string subString;

	while (getline(ss, subString, '\n'))
	{
		wires.push_back(Wire(subString));
	}

	return wires;
}

int FindClosestIntersection(string const& input)
{
	auto const wires = GetWires(input);
	Point const centralPoint(0, 0);
	auto const intersections = FindIntersections(wires[0], wires[1]);
	auto const distances = FindDistancesFromPoint(centralPoint, intersections);
	auto const shortestDistance = FindShortestDistance(distances);
	return shortestDistance;
}

int FindDistanceFromPoint(Point const& central_point, Point const& intersection)
{
	auto const distanceX = abs(central_point.GetX() - intersection.GetX());
	auto const distanceY = abs(central_point.GetX() - intersection.GetY());
	return distanceX + distanceY;
}

int FindShortestDistance(std::list<int> const& distances)
{
	auto min = distances.front();

	for(auto& distance : distances)
	{
		if (distance < min)
			min = distance;
	}

	return min;
}
