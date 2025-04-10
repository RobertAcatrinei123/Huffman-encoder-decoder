#pragma once
#include <cstdint>
#include <fstream>
#include "code.h"

class Node
{
private:
	uint8_t data;
	Node* left, * right;
	uint64_t freq;
public:
	Node();
	Node(const Node& other);
	Node(uint8_t data, uint64_t freq);
	Node(Node left, Node right);
	~Node();
	bool operator<(const Node& other)const;
	Node& operator=(const Node& other);
	void debug()const;
	uint64_t getFreq()const;
	void populateCodeTable(Code *codetable,Code &tmp);
	void printTree(std::ofstream &out);
};
