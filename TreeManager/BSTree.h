#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <queue>

class BSTree
{
public:
	class Node
	{
	public:
		Node(int data) : data(data) {}
		int data{};
		Node* left{};
		Node* right{};
	};

	BSTree();
	~BSTree();
	void DeleteBSTree(Node* node);

	Node* GetMaximum(Node* node);
	Node* GetMinimum(Node* node);

	void Insert(Node*& node, int data);
	void Insert(int data);
	void RemoveNode(Node*& node, int data);
	void RemoveNode(int data);
	bool isEmpty();
	Node* FindNode(int data);
	int getHeight(Node* node);
	int getHeight();
	Node*& getRoot();
	int NodeCount(Node* node);
	int NodeCount();
	int CountNodesOnLevel(Node* node, int level);
	int CountNodesOnLevel(int level);

	void PrintVerticalWithBranches();
	void PrintVertical();

	void PrintHorizontalWithBranches(Node* node, std::string rightPrefix = "", std::string currPrefix = "", std::string leftPrefix = "");
	void PrintHorizontalWithBranches(std::string rightPrefix = "", std::string currPrefix = "", std::string leftPrefix = "");
	void PrintHorizontal(Node* node, int n = 1);
	void PrintHorizontal(int n = 1);

	// обходы дерева
	//1. симметричный обход(лево, корень, право)
	void InorderTraversal(Node* node);
	void InorderTraversal();
	//2. прямой обход (корень, лево, право)
	void PreorderTraversal(Node* node);
	void PreorderTraversal();
	//3. обратный обход (лево, право, корень)
	void PostorderTraversal(Node* node);
	void PostorderTraversal();

	std::string getInorderTraversal(Node* node);
	std::string getInorderTraversal();

private:
	void PrintCentred(std::string str, int width);
	Node* root{};
};

