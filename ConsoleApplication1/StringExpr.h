#pragma once
#include <string>
#include "Expression.h"

class StringExpr : public Expression { // 문자열 저장 클래스

public:
    std::string value;

    StringExpr(const std::string& v) : value(v) {} // 값을 복사하지 않기 위해 참조 타입으로 받음.
    // const로 만들어서 임시 객체를 받을수 있도록 함. 즉, 매개변수로 곧바로 "aa"와 같은걸 넣어도 되게끔.
    // 대신 함수 내부에서 수정 불가능.

    std::variant<int, std::string> eval() override {
        return value; // 문자열 그대로 리턴. 따로 해야하는 작업 없음.
    }
};