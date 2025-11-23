#pragma once

#include <unordered_map>
#include <string>
#include "FunctionStruct.h"

struct ClassStruct {
	std::string name;
	std::unordered_map<std::string, FunctionStruct> methods;
};
