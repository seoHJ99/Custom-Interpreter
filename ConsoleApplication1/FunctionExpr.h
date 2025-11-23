#pragma once
#include "Expression.h"
#include <unordered_map>
#include <string>


std::unordered_map<std::string, std::string> funcContents;

class FunctionExpr : public Expression {

    std::string name;

    FunctionExpr(const std::string& n) : name(n) {}

    std::variant<int, std::string> eval() override {
        if (funcContents.find(name) == funcContents.end()) {
            throw std::runtime_error("정체 불명의 함수 이름. 값이 없음: " + name);
        }
        return funcContents[name]; // 맵에 저장된 값 리턴.
    }
};
