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
	int GetOrbitSum(const std::string& key, int depth);
	
	std::vector<std::string> GetConnectedEdges(std::string const& edge);
	std::vector<std::string> FindRoute(std::string const& target);
	int FindMinOrbitDistance(std::string const& obj1, std::string const& obj2);

private:
	std::map<std::string, std::vector<std::string>> adjList;

	
};
