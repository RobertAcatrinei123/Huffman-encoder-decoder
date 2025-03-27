#include <iostream>
#include <string>

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
			infile = argv[i];
		}
		if (strcmp("-o", argv[i]) == 0)
		{
			i++;
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
}