#pragma once
#include <utility>
#include <xstring>
#include <vector>
#include <map>

class Node
{
public:
	explicit Node(std::string data) : data(std::move(data)) {}

	void AddChild(Node* child) { children.push_back(child); }
	void SetParent(Node* parent) { this->parent = parent; }
	Node* GetParent() const { return parent; }
	std::vector<Node*> const& GetChildren() const { return children; }
	auto GetNumberOfChildren() const { return children.size(); }
	std::string GetData() const { return data; }
private:
	std::string data;
	Node* parent = nullptr;
	std::vector<Node*> children;
};

class OrbitTree
{

public:
	OrbitTree();
	Node* CopyTreeRecursively(Node const& parent);
	OrbitTree(OrbitTree const& other);
	~OrbitTree();
	Node* CreateNode(std::string const& data);
	Node* FindNode(std::string const& data);
	void AddEdge(std::string const& text);
	int GetOrbitSum() const;
	int GetOrbitSum(Node const* parent, int depth) const;

	std::vector<std::string> GetChildren(const std::string& target);
	std::vector<std::string> FindRoute(std::string const& target) const;
	bool FindRoute(std::string const& target, Node const* parent, std::vector<std::string>& route) const;
	int FindMinOrbitDistance(std::string const& obj1, std::string const& obj2) const;

private:

	Node* root;
	std::vector<Node*> nodes;
};


