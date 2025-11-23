#pragma once
#include <variant>
#include <string>
#include <memory>
#include <iostream>

//using Value = std::variant<int, std::string>;

class Expression {
public:
    virtual std::variant<int, std::string> eval() = 0;

    virtual ~Expression() {}
};