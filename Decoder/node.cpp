#include "node.h"
#include <iostream>

Node::Node() :data(0), left(nullptr), right(nullptr) {}
Node::Node(const Node& other) :data(other.data)
{
	left = nullptr;
	right = nullptr;
	if (other.left)left = new Node(*other.left);
	if (other.right)right = new Node(*other.right);
}
Node::Node(uint8_t data) :data(data), left(nullptr), right(nullptr) {}
Node::Node(Node left, Node right) :data(0){
	this->left = new Node(left);
	this->right = new Node(right);
}
Node::~Node()
{
	if (left)delete left;
	if (right)delete right;
}

void Node::debug()const
{
	std::cerr << data << '\n';
	if (left)
	{
		std::cerr << "left\n";
		left->debug();
		std::cerr << "back left\n";
	}
	if (right)
	{
		std::cerr << "right\n";
		right->debug();
		std::cerr << "back right\n";
	}
}


Node& Node::operator=(const Node& other)
{
	data = other.data;
	if (other.left)left = new Node(*other.left);
	else left = nullptr;
	if (other.right)right = new Node(*other.right);
	else right = nullptr;
	return *this;
}

char Node::getChar(Reader& reader)const
{
	if (left == nullptr && right == nullptr)
	{
		return data;
	}
	else
	{
		bool bit = reader.nextBit();
		if (bit)
		{
			return right->getChar(reader);
		}
		else
		{
			return left->getChar(reader);
		}
	}
}