#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>
#include "node.h"

std::pair<std::vector<int>,std::string> read(std::istream* in);
Node* createTree(std::vector<int>& histogram);