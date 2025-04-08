#include "printer.h"
#include <iostream>

Printer::Printer(std::ofstream& out):out(out)
{
	data = 0;
	size = 0;
}

void Printer::print(bool bit)
{
	if (size == 8)flush();
	data |= (bit << size);
	size++;
}

void Printer::flush()
{
	out.write((char*)&data, sizeof(data));
	data = 0;
	size = 0;
}