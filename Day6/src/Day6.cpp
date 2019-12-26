#include "Day6.h"
#include <string>
#include <fstream>
#include <exception>
#include <stack>
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

int DiGraph::GetOrbitSum(string const& key, int const depth)
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

std::vector<std::string> DiGraph::GetConnectedEdges(string const& edge)
{
	//if (adjList.find(edge) == adjList.end())
	//	throw exception("No element");
	return adjList[edge];
}

std::vector<std::string> DiGraph::FindRoute(string const& target)
{
	vector<string> route;
	string const root = "COM";
	
	stack<string> pathStack;
	for (auto const& objs: adjList[root])
	{
		pathStack.push(objs);
	}

	route.push_back("COM");
	
	while (!pathStack.empty())
	{
		string currentObj = pathStack.top();
		pathStack.pop();
		if (currentObj == target)
		{
			return route;
		}
		if(adjList.find(currentObj) != adjList.end())
		{
			route.push_back(currentObj);
			
			for (auto const& childValue : adjList[currentObj])
				pathStack.push(childValue);
		}
		else 
		{
			route.pop_back();
		}
	}

	throw exception("Target not found");
}

int DiGraph::FindMinOrbitDistance(string const& obj1, string const& obj2)
{
	auto obj1Route = FindRoute(obj1);
	auto obj2Route = FindRoute(obj2);

	while(!obj1Route.empty())
	{
		if (obj1Route[1] == obj2Route[1])
		{
			obj1Route.erase(obj1Route.begin());
			obj2Route.erase(obj2Route.begin());
		}
		else
		{
			obj1Route.erase(obj1Route.begin());
			obj2Route.erase(obj2Route.begin());
			return obj1Route.size() + obj2Route.size();
		}
	}
	
	return 1;
}
