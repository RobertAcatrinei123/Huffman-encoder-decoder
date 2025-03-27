#pragma once
#include <cstdint>

class Node
{
private:
	uint8_t data;
	Node* left, * right;
	uint64_t freq;
public:
	Node();
	Node(uint8_t data, uint64_t freq);
	Node(uint64_t freq,Node *left,Node *right);
	~Node();
};