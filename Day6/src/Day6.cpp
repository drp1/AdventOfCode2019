#include "Day6.h"
#include <string>
#include <fstream>
#include <exception>
#include <stack>
using namespace std;

OrbitTree::OrbitTree()
{
	root = CreateNode("COM");
}

Node* OrbitTree::CreateNode(std::string const& data)
{
	if (FindNode(data) != nullptr)
		throw exception("Node already exists");
	
	Node* newNode = new Node(data);
	nodes.push_back(newNode);
	return newNode;
}

Node* OrbitTree::FindNode(std::string const& data)
{
	for (auto const node : nodes)
	{
		if (node->GetData() == data)
			return node;
	}
	return nullptr;
}

void OrbitTree::AddEdge(string const& text)
{
	auto const separator = text.find(')');
	string const parentStr = text.substr(0, separator);
	string const childStr = text.substr(separator + 1, text.length() - separator - 1);

	Node* parentNode = FindNode(parentStr);
	if(parentNode == nullptr)
		parentNode = CreateNode(parentStr);

	Node* childNode = FindNode(childStr);
	if (childNode == nullptr)
		childNode = CreateNode(childStr);
	
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

std::vector<std::string> OrbitTree::GetChildren(std::string const& target)
{
	Node* targetNode = FindNode(target);
	if (targetNode != nullptr)
	{
		vector<string> childrenStrings;

		for (auto const* child : targetNode->GetChildren())
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
			return static_cast<int>(obj1Route.size() + obj2Route.size());
		}
	}
	
	return 1;
}
