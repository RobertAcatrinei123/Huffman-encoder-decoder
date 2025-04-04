#include "node.h"
#include <iostream>

Node::Node() :data(0), freq(0), left(nullptr), right(nullptr) {}
Node::Node(const Node& other) :data(other.data), freq(other.freq) 
{
	left = nullptr;
	right = nullptr;
	if (other.left)left = new Node(*other.left);
	if (other.right)right = new Node(*other.right);
}
Node::Node(uint8_t data, uint64_t freq) :data(data), freq(freq), left(nullptr), right(nullptr) {}
Node::Node(Node left, Node right) :data('$'), freq((left.freq) + (right.freq))
{
	this->left = new Node(left);
	this->right = new Node(right);
}
Node::~Node()
{
	if (left)delete left;
	if (right)delete right;
}

bool Node::operator<(const Node& other)const
{
	return freq > other.freq;
}

void Node::debug()const 
{
	std::cerr << data << ' ' << freq << '\n';
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

uint64_t Node::getFreq()const
{
	return freq;
}

Node& Node::operator=(const Node& other)
{
	data = other.data;
	freq = other.freq;
	if (other.left)left = new Node(*other.left);
	else left = nullptr;
	if (other.right)right = new Node(*other.right);
	else right = nullptr;
	return *this;
}