#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include "huffman.h"
#include "defines.h"

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

	auto res = read(in);
	auto histogram = res.first;
	auto text = res.second;
	auto root = createTree(histogram);
	long long tmp = MAGIC;

	out.write((char*) & tmp, 4);
	out.close();
	return 0;
}