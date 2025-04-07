#pragma once
#include <cstdint>

class Node
{
private:
	uint8_t data;
	Node* left, * right;
public:
	Node();
	Node(const Node& other);
	Node(uint8_t data);
	Node(Node left, Node right);
	~Node();
	bool operator<(const Node& other)const;
	Node& operator=(const Node& other);
	void debug()const;
	uint64_t getFreq()const;
};
