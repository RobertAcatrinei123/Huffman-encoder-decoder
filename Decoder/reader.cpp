#include "reader.h"
#include <iostream>

Reader::Reader(std::ifstream& in):in(in)
{
	data = 0;
	size = 8;
}
void Reader::nextByte()
{
	in.read((char*)&data, sizeof(data));
	size = 0;
}
bool Reader::nextBit()
{
	if (size == 8)nextByte();
	bool ret = data & (1 << (size++));
	return ret;
}