#include "huffman.h"
#include "node.h"
#include <queue>

std::pair<std::vector<int>, std::string> read(std::istream* in)
{
	std::vector<int> result(256,0);
	std::string str="";
	uint8_t c;
	std::string tmp;
	while (!in->eof())
	{
		c = in->get();
		str.push_back(c);
		result[c]++;
	}
	result[255] = 0;
	str.pop_back();
	return { result ,str };
}

Node* createTree(std::vector<int>& histogram)
{
	auto pq = std::priority_queue<Node>();
	for (int i = 0;i < histogram.size();i++)
	{
		if (histogram[i] > 0)pq.push(Node(i, histogram[i]));
	}
	while (pq.size() > 1)
	{
		auto left = pq.top();
		pq.pop();
		auto right = pq.top();
		pq.pop();
		pq.push(Node(left, right));
	}
	return new Node(pq.top());
}