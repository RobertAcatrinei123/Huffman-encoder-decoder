#pragma once
#include <cstdint>
#include <fstream>

class Reader
{
private:
	uint8_t data;
	uint8_t size;
	std::ifstream& in;
	void nextByte();
public:
	Reader(std::ifstream &in);
	bool nextBit();
};