#pragma once
#include <xstring>
#include <vector>
#include <map>


class DiGraph
{
public:
	DiGraph() = default;
	void AddEdge(std::string const& text);
	int GetOrbitSum();
	int GetOrbitSum(std::string key, int depth);
	
	std::vector<std::string> GetConnectedEdges(std::string const& edge);
	
private:
	std::map<std::string, std::vector<std::string>> adjList;

	
};
