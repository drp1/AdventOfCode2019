#include "Day6.h"
#include <string>
#include <fstream>
#include <exception>
using namespace std;

//DiGraph::DiGraph(string const& filePath)
//{
//	ifstream fin(filePath);
//	if (!fin.is_open())
//		throw exception("File not found");
//
//	string line;
//	while (getline(fin, line))
//	{
//		AddEdge(line);
//	}
//	fin.close();
//}
//

void DiGraph::AddEdge(string const& text)
{
	int const separator = text.find(')');
	string const start = text.substr(0, separator);
	string const end = text.substr(separator + 1, text.length() - separator - 1);

	if (adjList.find(start) == adjList.end())
	{
		adjList[start] = vector<string>();
	}
	adjList[start].push_back(end);
}


int DiGraph::GetOrbitSum()
{
	string const root = "COM";
	int const depth = 1;
	int const sum = GetOrbitSum(root, depth);
	return sum;
}

int DiGraph::GetOrbitSum(string const key, int const depth)
{
	int sum = 0;
	for (auto const& value : adjList[key])
	{
		if (adjList.find(value) != adjList.end())
		{
			sum += GetOrbitSum(value, depth + 1);
		}
		sum += depth;
	}
	return sum;
}


std::vector<std::string> DiGraph::GetConnectedEdges(std::string const& edge)
{
	//if (adjList.find(edge) == adjList.end())
	//	throw exception("No element");
	return adjList[edge];
}