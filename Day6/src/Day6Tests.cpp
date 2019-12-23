#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Day6.h"
#include <fstream>

using namespace std;
using namespace testing;


TEST(Day6TestSuite, Should_Parse_All_Lines_In_File)
{
	DiGraph graph;
	string const filePath = "src/TestInput1.txt";
	ifstream fin(filePath);
	if (!fin.is_open())
		throw exception("File not found");

	string line;
	while (getline(fin, line))
	{
		graph.AddEdge(line);
	}
	fin.close();

	EXPECT_THAT(graph.GetConnectedEdges("COM"), UnorderedElementsAre("B"));
	EXPECT_THAT(graph.GetConnectedEdges("B"), UnorderedElementsAre("C", "G"));
	EXPECT_THAT(graph.GetConnectedEdges("C"), UnorderedElementsAre("D"));
	EXPECT_THAT(graph.GetConnectedEdges("D"), UnorderedElementsAre("I", "E"));
	EXPECT_THAT(graph.GetConnectedEdges("E"), UnorderedElementsAre("J", "F"));
	EXPECT_THAT(graph.GetConnectedEdges("F"), IsEmpty());
	EXPECT_THAT(graph.GetConnectedEdges("G"), UnorderedElementsAre("H"));
	EXPECT_THAT(graph.GetConnectedEdges("H"), IsEmpty());
	EXPECT_THAT(graph.GetConnectedEdges("I"), IsEmpty());
	EXPECT_THAT(graph.GetConnectedEdges("J"), UnorderedElementsAre("K"));
	EXPECT_THAT(graph.GetConnectedEdges("K"), UnorderedElementsAre("L"));
	EXPECT_THAT(graph.GetConnectedEdges("L"), IsEmpty());
}


TEST(Day6TestSuite, Should_Sum_Direct_And_Indirect_Orbits)
{
	DiGraph graph;
	string const filePath = "src/TestInput1.txt";
	ifstream fin(filePath);
	if (!fin.is_open())
		throw exception("File not found");

	string line;
	while (getline(fin, line))
	{
		graph.AddEdge(line);
	}
	fin.close();

	int const expectedOrbitSum = 42;
	EXPECT_EQ(graph.GetOrbitSum(), expectedOrbitSum);
}


TEST(Day6TestSuite, Part1)
{
	DiGraph graph;
	string const filePath = "src/input.txt";
	ifstream fin(filePath);
	if (!fin.is_open())
		throw exception("File not found");

	string line;
	while (getline(fin, line))
	{
		graph.AddEdge(line);
	}
	fin.close();

	int const expectedOrbitSum = 453028;
	int const actualOutput = graph.GetOrbitSum();
	cout << "Output: " << actualOutput << endl;
	EXPECT_EQ(actualOutput, expectedOrbitSum);
}
