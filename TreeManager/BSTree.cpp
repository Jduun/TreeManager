#include "BSTree.h"

BSTree::BSTree() {}

BSTree::~BSTree()
{
	DeleteBSTree(root);
}

void BSTree::DeleteBSTree(Node* node)
{
	if (node)
	{
		DeleteBSTree(node->right);
		DeleteBSTree(node->left);
		delete node;
	}
}

int BSTree::NodeCount(Node* node)
{
	if (!node)
	{
		return 0;
	}
	if (!node->left && !node->right)
	{
		return 1;
	}
	int left{}, right{};
	if (node->left)
	{
		left = NodeCount(node->left);
	}
	if (node->right)
	{
		right = NodeCount(node->right);
	}
	return left + right + 1;
}

int BSTree::NodeCount()
{
	return NodeCount(root);
}

bool BSTree::isEmpty()
{
	return NodeCount() == 0;
}

void BSTree::Insert(Node*& node, int data)
{
	if (!node)
	{
		node = new Node(data);
	}
	else if (data < node->data)
	{
		Insert(node->left, data);
	}
	else if (data > node->data)
	{
		Insert(node->right, data);
	}
}

void BSTree::Insert(int data)
{
	Insert(root, data);
}

void BSTree::RemoveNode(Node*& node, int data)
{
	if (!node)
	{
		return;
	}
	if (data == node->data)
	{
		if (!node->left && !node->right) // если узел - лист
		{
			delete node;
			node = nullptr;
		}
		else if (!node->left && node->right) // у узла - правый потомок
		{
			Node* temp = node->right;
			delete node; // вынести общую часть
			node = temp;
		}
		else if (node->left && !node->right) // у узла - левый потомок
		{
			Node* temp = node->left;
			delete node;
			node = temp;
		}
		else // у узла 2 потомка
		{
			node->data = GetMinimum(node->right)->data;
			RemoveNode(node->right, node->data);
		}
		return;
	}
	if (data < node->data)
	{
		RemoveNode(node->left, data);
	}
	else if (data > node->data)
	{
		RemoveNode(node->right, data);
	}
}

void BSTree::RemoveNode(int data)
{
	RemoveNode(root, data);
}

BSTree::Node*& BSTree::getRoot()
{
	return root;
}

int BSTree::getHeight(Node* node)
{
	if (!node)
	{
		return -1;
	}
	return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

BSTree::Node* BSTree::GetMinimum(Node* node)
{
	if (!node->left)
	{
		return node;
	}
	return GetMinimum(node->left);
}

BSTree::Node* BSTree::GetMaximum(Node* node)
{
	if (!node->right)
	{
		return node;
	}
	return GetMaximum(node->right);
}

void BSTree::PrintHorizontalWithBranches(Node* node, std::string rightPrefix, std::string currPrefix, std::string leftPrefix)
{
	const std::string LEFT_BRANCH = "\\-";
	const std::string RIGHT_BRANCH = "/-";
	const std::string BRANCH = "| ";
	if (!node)
	{
		return;
	}
	if (node->right)
	{
		PrintHorizontalWithBranches(node->right, rightPrefix + "  ", rightPrefix + RIGHT_BRANCH, rightPrefix + BRANCH);
	}
	std::cout << currPrefix << node->data << std::endl;
	if (node->left)
	{
		PrintHorizontalWithBranches(node->left, leftPrefix + BRANCH, leftPrefix + LEFT_BRANCH, leftPrefix + "  ");
	}
}

void BSTree::PrintHorizontalWithBranches(std::string rightPrefix, std::string currPrefix, std::string leftPrefix)
{
	PrintHorizontalWithBranches(root);
}

void BSTree::PrintHorizontal(Node* node, int n)
{
	if (!node)
	{
		std::cout << std::endl;
		return;
	}
	int maxLengthData = std::to_string(GetMaximum(root)->data).length();
	PrintHorizontal(node->right, n + maxLengthData);
	for (int i = 0; i < n; i++)
	{
		std::cout << " ";
	}
	std::cout << node->data;
	PrintHorizontal(node->left, n + maxLengthData);
}

void BSTree::PrintHorizontal(int n)
{
	PrintHorizontal(root, n);
}

// не доработано
void BSTree::PrintVerticalWithBranches()
{
	const int CELL_WIDTH = std::to_string(GetMaximum(root)->data).length();
	if (!root)
	{
		return;
	}
	int height = getHeight(root);
	int currWidth = CELL_WIDTH * std::pow(height, 2);
	std::queue<Node*> nodes;
	nodes.push(root);
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j < std::pow(2, i); j++)
		{
			Node* currNode = nodes.front();
			nodes.pop();
			if (currNode)
			{
				nodes.push(currNode->left);
				nodes.push(currNode->right);
				std::string str = std::to_string(currNode->data);
				int width = currWidth;
				int leadingSpaces = width / 2 - str.length() / 2;
				int postSpaces = width - leadingSpaces - str.length();

				for (int i = 0; i < leadingSpaces / 2 - 1; i++)
				{
					std::cout << " ";
				}
				std::cout << "/";

				for (int i = 0; i < leadingSpaces - leadingSpaces / 2 + 1; i++)
				{
					std::cout << "-";
				}
				std::cout << str;

				for (int i = 0; i < postSpaces / 2 - 1; i++)
				{
					std::cout << "-";
				}
				std::cout << "\\";
			}
			else
			{
				nodes.push(nullptr);
				nodes.push(nullptr);
				std::cout << std::setw(currWidth) << "";
			}
		}
		currWidth /= 2;
		std::cout << std::endl;
	}
}

void BSTree::PrintVertical()
{
	const int CELL_WIDTH = std::to_string(GetMaximum(root)->data).length();
	if (!root)
	{
		return;
	}
	int height = getHeight(root);
	int currWidth = CELL_WIDTH * std::pow(height, 2);
	std::queue<Node*> nodes;
	nodes.push(root);
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j < std::pow(2, i); j++)
		{
			Node* currNode = nodes.front();
			nodes.pop();
			if (currNode)
			{
				nodes.push(currNode->left);
				nodes.push(currNode->right);
				PrintCentred(std::to_string(currNode->data), currWidth);
			}
			else
			{
				nodes.push(nullptr);
				nodes.push(nullptr);
				std::cout << std::setw(currWidth) << "";
			}
		}
		currWidth /= 2;
		std::cout << std::endl;
	}
}

void BSTree::InorderTraversal(Node* node)
{
	if (!node)
	{
		return;
	}
	InorderTraversal(node->left);
	std::cout << node->data << " ";
	InorderTraversal(node->right);
}

void BSTree::InorderTraversal()
{
	InorderTraversal(root);
}

void BSTree::PreorderTraversal(Node* node)
{
	if (!node)
	{
		return;
	}
	std::cout << node->data << " ";
	PreorderTraversal(node->left);
	PreorderTraversal(node->right);
}

void BSTree::PreorderTraversal()
{
	PreorderTraversal(root);
}

void BSTree::PostorderTraversal(Node* node)
{
	if (!node)
	{
		return;
	}
	PreorderTraversal(node->left);
	PreorderTraversal(node->right);
	std::cout << node->data << " ";
}

void BSTree::PostorderTraversal()
{
	PostorderTraversal(root);
}

BSTree::Node* BSTree::FindNode(int data)
{
	Node* curr = root;
	while (curr)
	{
		if (data == curr->data)
		{
			return curr;
		}
		curr = (data < curr->data ? curr->left : curr->right);
	}
	return nullptr;
}

void BSTree::PrintCentred(std::string str, int width)
{
	int leadingSpaces = width / 2 - str.length() / 2;
	int postSpaces = width - leadingSpaces - str.length();
	std::cout << std::setw(leadingSpaces) << " " << str << std::setw(postSpaces) << " ";
}

int BSTree::CountNodesOnLevel(Node* node, int level)
{
	if (!node)
	{
		return 0;
	}
	if (level == 0)
	{
		return 1;
	}
	return CountNodesOnLevel(node->left, level - 1) + CountNodesOnLevel(node->right, level - 1);
}

int BSTree::CountNodesOnLevel(int level)
{
	return CountNodesOnLevel(root, level);
}

int BSTree::getHeight()
{
	return getHeight(root);
}

std::string BSTree::getInorderTraversal(Node* node)
{
	if (!node)
	{
		return "";
	}
	return getInorderTraversal(node->left) + " " + std::to_string(node->data) + " " + getInorderTraversal(node->right);
}

std::string BSTree::getInorderTraversal()
{
	return getInorderTraversal(root) + "\n";
}