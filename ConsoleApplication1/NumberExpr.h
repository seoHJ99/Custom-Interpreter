#pragma once
#include "Expression.h"

class NumberExpr : public Expression { // 숫자 표현 저장 클래스

public:
	int value;

    NumberExpr(int v) : value(v) {} // 멤버 초기화 리스트. 생성자가 실행되기 전에 멤버로 바로 초기화함. 불필요한 생성자 호출이 없어서 효율이 더 좋음

    std::variant<int, std::string> eval() override {
        return value; // 숫자 그대로 리턴. 따로 해야하는 작업 없음.
    }
};