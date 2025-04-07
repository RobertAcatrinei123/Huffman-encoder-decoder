#include "node.h"
#include <iostream>
#include <fstream>

Node::Node() :data(0), freq(0), left(nullptr), right(nullptr) {}
Node::Node(const Node& other) :data(other.data), freq(other.freq) 
{
	left = nullptr;
	right = nullptr;
	if (other.left)left = new Node(*other.left);
	if (other.right)right = new Node(*other.right);
}
Node::Node(uint8_t data, uint64_t freq) :data(data), freq(freq), left(nullptr), right(nullptr) {}
Node::Node(Node left, Node right) :data(0), freq((left.freq) + (right.freq))
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

void Node::populateCodeTable(Code* codetable, Code tmp)
{
	if (left)
	{
		tmp.push(0);
		left->populateCodeTable(codetable, tmp);
		tmp.pop();
	}
	if (right)
	{
		tmp.push(1);
		right->populateCodeTable(codetable, tmp);
		tmp.pop();
	}
	if (!left && !right)
	{
		codetable[data] = tmp;
	}
}

void Node::printTree(std::ofstream& out)
{
	if (left)
	{
		left->printTree(out);
	}
	if (right)
	{
		right->printTree(out);
	}
	if (right || left)
	{
		const char tmp = 'I';
		out.write(&tmp, sizeof(tmp));
	}
	else
	{
		const char tmp = 'L';
		out.write(&tmp, sizeof(tmp));
		out.write((char *) & data, sizeof(tmp));
	}
}
