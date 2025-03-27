#include "node.h"

Node::Node() :data(0), freq(0), left(nullptr), right(nullptr) {}
Node::Node(uint8_t data, uint64_t freq) :data(data), freq(freq), left(nullptr), right(nullptr) {}
Node::Node(uint64_t freq, Node* left, Node* right) :data(0), freq(freq), left(left), right(right) {}
Node::~Node()
{
	if (left != nullptr)delete left;
	if (right != nullptr)delete right;
}