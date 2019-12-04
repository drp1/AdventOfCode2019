#include "Day 3.h"
#include <list>

#include "gtest/gtest.h"

using namespace std;


Wire GetWire1(string input) 
{
	return Wire();
}

Wire GetWire2(string input)
{
	return Wire();
}


int FindClosestIntersection(string input)
{
	Wire wire1 = GetWire1(input);
	Wire wire2 = GetWire2(input);

	//list<WireIntersection> intersections = FindIntersections(wire1, wire2);

	//for (WireSegment wire1Segment : wire1.Segments())
	//{
	//	for (WireSegment wire2Segment : wire2.Segments())
	//	{

	//	}

	//}



	return 0;
}

namespace Day3::tests
{
	TEST(Day3TestSuite, ExampleInput1Test)
	{
		string testInput = "R8,U5,L5,D3\nU7,R6,D4,L4";
		int expectedDistance = 159;
		EXPECT_EQ(expectedDistance, FindClosestIntersection(testInput));
	}
	TEST(Day3TestSuite, ExampleInput2Test)
	{
		string testInput = "R75,D30,R83,U83,L12,D49,R71,U7\nL72, U62, R66, U55, R34, D71, R55, D58, R83";
		int expectedDistance = 159;
		EXPECT_EQ(expectedDistance, FindClosestIntersection(testInput));
	}

	TEST(Day3TestSuite, ExampleInput3Test)
	{
		string testInput = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51\nU98, R91, D20, R16, D67, R40, U7, R15, U6, R7";
		int expectedDistance = 135;
		EXPECT_EQ(expectedDistance, FindClosestIntersection(testInput));
	}

}