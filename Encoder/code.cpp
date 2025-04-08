#include "code.h"
#include <vcruntime_string.h>

Code::Code():size(0)
{
	memset(data,0,sizeof data);
}
Code::Code(uint16_t size, uint8_t data[MAX_CODE_SIZE]) :size(size) 
{
	for (int i = 0;i < MAX_CODE_SIZE;i++)this->data[i] = data[i];
}
void Code::push(bool bit)
{
	data[size/8] |= (bit << (size%8));
	size++;
}
bool Code::pop()
{
	size--;
	bool bit = data[size/8] & (1 << (size%8));
	data[size/8] &= ~(1 << (size%8));
	return bit;
}

bool Code::canPop()
{
	return size != 0;
}

Code::Code(const Code& other)
{
	size = other.size;
	memset(data, 0, sizeof data);
	for (int i = 0;i < MAX_CODE_SIZE;i++)data[i] = other.data[i];
}

Code& Code::operator=(const Code& other)
{
	size = other.size;
	memset(data, 0, sizeof data);
	for (int i = 0;i < MAX_CODE_SIZE;i++)data[i] = other.data[i];
	return *this;
}
