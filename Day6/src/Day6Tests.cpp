#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Day6.h"
#include <fstream>

using namespace std;
using namespace testing;


OrbitTree BuildGraph(string const& filePath)
{
	OrbitTree graph;
	ifstream fin(filePath);
	if (!fin.is_open())
		throw exception("File not found");

	string line;
	while (getline(fin, line))
	{
		graph.AddEdge(line);
	}
	fin.close();

	return graph;
}

TEST(Day6TestSuite, Should_Parse_All_Lines_In_File)
{
	string const filePath = "src/TestInput1.txt";
	OrbitTree graph = BuildGraph(filePath);

	EXPECT_THAT(graph.GetChildren("COM"), UnorderedElementsAre("B"));
	EXPECT_THAT(graph.GetChildren("B"), UnorderedElementsAre("C", "G"));
	EXPECT_THAT(graph.GetChildren("C"), UnorderedElementsAre("D"));
	EXPECT_THAT(graph.GetChildren("D"), UnorderedElementsAre("I", "E"));
	EXPECT_THAT(graph.GetChildren("E"), UnorderedElementsAre("J", "F"));
	EXPECT_THAT(graph.GetChildren("F"), IsEmpty());
	EXPECT_THAT(graph.GetChildren("G"), UnorderedElementsAre("H"));
	EXPECT_THAT(graph.GetChildren("H"), IsEmpty());
	EXPECT_THAT(graph.GetChildren("I"), IsEmpty());
	EXPECT_THAT(graph.GetChildren("J"), UnorderedElementsAre("K"));
	EXPECT_THAT(graph.GetChildren("K"), UnorderedElementsAre("L"));
	EXPECT_THAT(graph.GetChildren("L"), IsEmpty());
}

TEST(Day6TestSuite, Should_Sum_Direct_And_Indirect_Orbits)
{
	string const filePath = "src/TestInput1.txt";
	OrbitTree graph = BuildGraph(filePath);

	int const expectedOrbitSum = 42;
	EXPECT_EQ(graph.GetOrbitSum(), expectedOrbitSum);
}


TEST(Day6TestSuite, Part1)
{
	string const filePath = "src/input.txt";
	OrbitTree const orbitTree = BuildGraph(filePath);
	
	int const expectedOrbitSum = 453028;
	int const actualOutput = orbitTree.GetOrbitSum();
	cout << "Output: " << actualOutput << endl;
	EXPECT_EQ(actualOutput, expectedOrbitSum);
}


TEST(Day6TestSuite, Should_Find_Route_To_Target)
{
	string const filePath = "src/TestInput2.txt";
	OrbitTree graph = BuildGraph(filePath);
	
	vector<string> actualRouteYou = graph.FindRoute("YOU");
	EXPECT_THAT(actualRouteYou, ElementsAre("COM", "B", "C", "D", "E","J","K"));
	
	actualRouteYou = graph.FindRoute("SAN");
	EXPECT_THAT(actualRouteYou, ElementsAre("COM", "B", "C", "D", "I"));
}


TEST(Day6TestSuite, Should_Find_Minimum_Orbit_Distance_Between_Objects)
{
	string const filePath = "src/TestInput2.txt";
	OrbitTree graph = BuildGraph(filePath);

	int const expectedMinDistance = 4;
	int const actualMinDistance = graph.FindMinOrbitDistance("YOU", "SAN");
	EXPECT_EQ(actualMinDistance, expectedMinDistance);
}

TEST(Day6TestSuite, Part2)
{
	string const filePath = "src/input.txt";
	OrbitTree graph = BuildGraph(filePath);


	int const expectedMinDistance = 562;
	int const actualMinDistance = graph.FindMinOrbitDistance("YOU", "SAN");
	cout << "Output: " << actualMinDistance << endl;
	EXPECT_EQ(actualMinDistance, expectedMinDistance);
}