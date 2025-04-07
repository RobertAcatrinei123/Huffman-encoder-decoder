#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include "defines.h"
#include "node.h"
#include <stack>

int main(int argc, char* argv[])
{
	bool help = false;
	std::string infile = "";
	std::string outfile = "";
	bool statistics = false;
	for (int i = 1;i < argc;i++)
	{
		if (strcmp("-h", argv[i]) == 0)help = true;
		if (strcmp("-s", argv[i]) == 0)statistics = true;
		if (strcmp("-i", argv[i]) == 0)
		{
			i++;
			if (i >= argc)
			{
				std::cerr << "No input file specified\n";
				exit(1);
			}
			infile = argv[i];
		}
		if (strcmp("-o", argv[i]) == 0)
		{
			i++;
			if (i >= argc)
			{
				std::cerr << "No output file specified\n";
				exit(1);
			}
			outfile = argv[i];
		}
	}
	if (help)
	{
		std::cout << "An app for Huffman decoding a text\n";
		std::cout << "Arguments:\n";
		std::cout << "-h: Prints this message\n";
		std::cout << "-i infile: Specifies the input file to encode.\n";
		std::cout << "-o infile: Specifies the output file. Default: stdout\n";
		std::cout << "-s: Prints decompression statistics.\n";
		exit(0);
	}

	std::ifstream in;
	if (infile != "")
	{
		in.open(infile, std::ios::binary | std::ios::in);
	}
	else
	{
		std::cerr << "No input file specified\n";
		exit(1);
	}

	std::ofstream out;
	if (outfile != "")
	{
		out.open(outfile);
	}

	uint32_t tmp;
	in.read((char*)&tmp, sizeof(tmp));

	std::cerr << tmp<<" "<<MAGIC<<'\n';

	if (tmp != MAGIC)
	{
		std::cout << "MAGIC numbers don't match!\n";
		return 1;
	}

	uint16_t treeSize;
	in.read((char*)&treeSize, sizeof(treeSize));

	std::stack<Node> s;

	for (int i = 0;i < treeSize;i++)
	{
		char type;
		in.read(&type, sizeof(type));
		if (type == 'L')
		{
			char data;
			in.read(&data, sizeof(data));
			s.push(Node(data));
		}
		else
		{
			auto right = s.top();
			s.pop();
			auto left = s.top();
			s.pop();
			s.push(Node(left,right));
		}
	}
	auto root = new Node(s.top());
	s.pop();

	root->debug();

	return 0;
}