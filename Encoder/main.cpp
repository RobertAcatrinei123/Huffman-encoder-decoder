#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include "huffman.h"
#include "defines.h"
#include "code.h"
#include "printer.h"

int main(int argc, char* argv[])
{
	bool help=false;
	std::string infile="";
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
		std::cout << "An app for Huffman encoding a text\n";
		std::cout << "Arguments:\n";
		std::cout << "-h: Prints this message\n";
		std::cout << "-i infile: Specifies the input file to encode. Default: stdin\n";
		std::cout << "-o infile: Specifies the output file.\n";
		std::cout << "-s: Prints compression statistics.\n";
		exit(0);
	}

    std::istream* in = &std::cin;
	std::ifstream infileStream;
    if (infile != "")
    {
        infileStream.open(infile);
        if (!infileStream.is_open())
        {
            std::cerr << "Failed to open input file\n";
            exit(1);
        }
        in = &infileStream;
    }
	std::ofstream out;
    if (outfile != "")
    {
		out.open(outfile,std::ios::binary|std::ios::out);
    }
	else
	{
		std::cerr << "No output file specified\n";
		exit(1);
	}

	uint64_t filesize = 0;
	auto res = read(in,filesize);
	auto histogram = res.first;
	auto text = res.second;

	auto root = createTree(histogram);

	uint32_t tmp = MAGIC;
	out.write((char*) & tmp, sizeof(tmp));

	Code codetable[256];
	Code tmpcode = Code();
	root->populateCodeTable(codetable,tmpcode);

	for (int i = 0;i < 256;i++)
	{
		if (histogram[i] > 0)
		{
			std::cerr << uint8_t(i) << ' ';
			auto tmp = codetable[i];
			while (tmp.canPop())std::cerr << tmp.pop();
			std::cerr << '\n';
		}
	}

	uint16_t treeSize = 0;

	for (auto i : histogram)
	{
		if (i > 0)treeSize++;
	}

	treeSize = 2 * treeSize - 1;

	out.write((char *) & treeSize, sizeof(treeSize));
	root->printTree(out);

	out.write((char *) &filesize, sizeof(filesize));

	Printer printer{ out };

	for (char c : text)
	{
		auto tmp = codetable[c];
		Code tmprev;
		while (tmp.canPop())
		{
			tmprev.push(tmp.pop());
		}
		while (tmprev.canPop())
		{
			printer.print(tmprev.pop());
		}
	}
	printer.flush();

	out.close();
	return 0;
}