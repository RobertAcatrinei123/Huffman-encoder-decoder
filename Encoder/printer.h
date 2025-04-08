#pragma once
#include <cstdint>
#include <fstream>

class Printer
{
private:
	uint8_t data;
	int8_t size;
	std::ofstream& out;
public:
	Printer(std::ofstream &out);
	void print(bool bit);
	void flush();
};