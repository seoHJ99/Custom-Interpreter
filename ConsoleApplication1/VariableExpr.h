#pragma once
#include "Expression.h"
#include <unordered_map>
#include <string>
#include "Value.h"

std::unordered_map<std::string, Value> variables;


class VariableExpr : public Expression

{
public:
    std::string name;

    VariableExpr(const std::string& n) : name(n) {}

    std::variant<int, std::string> eval() override {
        if (variables.find(name) == variables.end()) {
            throw std::runtime_error("정체 불명의 변수. 값이 없음: " + name);
        }
        auto value = variables[name];
        if (value.type == TokenType::StringType && !std::holds_alternative<std::string>(value.value)) {
            throw std::runtime_error("string 타입 에러");
        }
        else if (value.type == TokenType::IntType && !std::holds_alternative<int>(value.value)) {
            throw std::runtime_error("int 타입 에러");
        }
        return variables[name].value; // 맵에 저장된 값 리턴.
    }
};
