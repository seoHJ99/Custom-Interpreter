#pragma once

#include "Expression.h"
#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> classes;

class ClassExpr : public Expression {
public:

    std::string name;

    ClassExpr(const std::string& n) : name(n) {}

    Value eval() override {

        if (classes.find(name) == classes.end()) {
            throw std::runtime_error("정체 불명의 클래스. 해당 값이 없음: " + name);
        }

        return classes[name]; // 맵에 저장된 값 리턴.
    }

};