#include "Day6.h"
#include <string>
#include <fstream>
#include <exception>
#include <stack>
using namespace std;

OrbitTree::OrbitTree()
{
	root = new Node("COM");
	stringToNodeMap[root->GetData()] = root;
}

void OrbitTree::AddEdge(string const& text)
{
	int const separator = text.find(')');
	string const parentStr = text.substr(0, separator);
	string const childStr = text.substr(separator + 1, text.length() - separator - 1);

	Node* childNode;
	Node* parentNode;
	
	if(stringToNodeMap.find(parentStr) == stringToNodeMap.end())
	{
		// Parent doesn't exist
		parentNode = new Node(parentStr);
		stringToNodeMap[parentStr] = parentNode;
	}
	else
	{
		parentNode = stringToNodeMap[parentStr];
	}
	
	if (stringToNodeMap.find(childStr) == stringToNodeMap.end())
	{
		// Child doesn't exist
		childNode = new Node(childStr);
		stringToNodeMap[childStr] = childNode;
	}
	else
	{
		childNode = stringToNodeMap[childStr];
	}
	
	
	childNode->SetParent(parentNode);
	parentNode->AddChild(childNode);
}


int OrbitTree::GetOrbitSum() const
{
	int const depth = 1;
	int const sum = GetOrbitSum(root, depth);
	return sum;
}

int OrbitTree::GetOrbitSum(Node const* parent, int const depth) const
{
	int sum = 0;
	for (auto const* child : parent->GetChildren())
	{
		if (child->GetNumberOfChildren() > 0)
		{
			sum += GetOrbitSum(child, depth + 1);
		}
		sum += depth;
	}
	return sum;
}

std::vector<std::string> OrbitTree::GetChildren(std::string target)
{
	if (stringToNodeMap.find(target) != stringToNodeMap.end())
	{
		vector<string> childrenStrings;

		for (auto const* child : stringToNodeMap[target]->GetChildren())
		{
			childrenStrings.push_back(child->GetData());
		}
		return childrenStrings;
	}

	throw exception("Target not found");
}

std::vector<std::string> OrbitTree::FindRoute(string const& target) const
{
	if (root->GetNumberOfChildren() == 0)
		throw exception("Target not found");
	
	vector<string> route;
	if (FindRoute(target, root, route))
	{
		route.insert(route.begin(), root->GetData());
		return route;
	}

	throw exception("Target not found");
}


bool OrbitTree::FindRoute(string const& target, Node const* parent, vector<string>& route) const
{	
	for (auto const* child : parent->GetChildren())
	{
		if (child->GetData() == target)
		{
			//route.insert(route.begin(), child->GetData());
			return true;
		}
		if (child->GetNumberOfChildren() > 0)
		{
			if (FindRoute(target, child, route))
			{
				route.insert(route.begin(), child->GetData());
				return true;
			}
		}
	}
	return false;
}


int OrbitTree::FindMinOrbitDistance(string const& obj1, string const& obj2) const
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
