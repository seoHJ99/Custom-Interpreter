#pragma once
#include <variant>
#include <string>
#include "TokenType.h"

struct Value {
	TokenType type ;
	std::variant<int, std::string> value;
};
