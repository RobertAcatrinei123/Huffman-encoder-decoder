#pragma once
#include <cstdint>
#include "defines.h"

class Code
{
private:
	uint16_t size;
	uint8_t data[MAX_CODE_SIZE];
public:
	Code();
	Code(uint16_t size, uint8_t data[MAX_CODE_SIZE]);
	Code(const Code& other);
	void push(bool bit);
	bool pop();
	bool canPop();
	Code& operator=(const Code& other);
};