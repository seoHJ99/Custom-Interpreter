#pragma once

#include <unordered_map>
#include <string>
#include <variant>

struct FunctionStruct {
	std::string name;
	std::unordered_map<std::string, std::variant<int, std::string>> params;
	std::unordered_map<std::string, std::string> methods;
};