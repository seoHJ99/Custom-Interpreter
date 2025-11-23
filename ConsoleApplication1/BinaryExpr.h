#pragma once
#include "Expression.h"
#include <iostream>
#include "VariableExpr.h"

class BinaryExpr : public Expression {
public:
	char value;
	std::unique_ptr<Expression> left, right;
	//using Value = std::variant<int, std::string>;

	// 단 하나만 소유 (unique) → 다른 포인터와 공유 불가
	// 객체가 더 이상 필요 없으면 자동으로 delete

	BinaryExpr(char o, std::unique_ptr<Expression> l, std::unique_ptr<Expression> r) :value(o), left(std::move(l)), right(std::move(r)) {}
	// left(std::move(l)) : left로 l의 소유권을 이동시킴. l의 값은 null, l은 null을 가리키는 nullptr(널 포인트 리터럴)이 됨.


	std::variant<int, std::string> eval() override {
		std::variant<int, std::string> left_val = left->eval();   // 왼쪽 피연산자 값
		std::variant<int, std::string> right_val = right->eval(); // 오른쪽 피연산자 값

		switch (value) {
		case '+':
			if (std::holds_alternative<int>(left_val) && std::holds_alternative<int>(right_val)) { //std::holds_alternative<int>(v) : 실제로 v의 타입이 int인지 확인
				int l = std::get<int>(left_val);   // Value 안의 int 꺼내기
				int r = std::get<int>(right_val);
				return l + r;
			}
			else if (std::holds_alternative<std::string>(left_val) && std::holds_alternative<std::string>(right_val)) {
				std::string l = std::get<std::string>(left_val);
				std::string r = std::get<std::string>(right_val);
				return l + r;
			}
			else if (std::holds_alternative<int>(left_val) && std::holds_alternative<std::string>(right_val)) {
				int l = std::get<int>(left_val);
				std::string r = std::get<std::string>(right_val);
				return std::to_string(l) + r;
			}
			else if (std::holds_alternative<std::string>(left_val) && std::holds_alternative<int>(right_val)) {
				std::string l = std::get<std::string>(left_val);
				int r = std::get<int>(right_val);
				return l + std::to_string(r);
			}
			else {
				throw std::runtime_error("잘못된 더하기 에러");
			}
		case '-':
			if (std::holds_alternative<int>(left_val) && std::holds_alternative<int>(right_val)) { //std::holds_alternative<int>(v) : 실제로 v의 타입이 int인지 확인
				int l = std::get<int>(left_val);   // Value 안의 int 꺼내기
				int r = std::get<int>(right_val);
				return l - r;
			}
		case '*':
			if (std::holds_alternative<int>(left_val) && std::holds_alternative<int>(right_val)) {
				int l = std::get<int>(left_val);
				int r = std::get<int>(right_val);
				return l * r;
			}
		case '/':
			if (std::holds_alternative<int>(left_val) && std::holds_alternative<int>(right_val)) {
				int l = std::get<int>(left_val);
				int r = std::get<int>(right_val);
				return l / r;
			}
		case '%':
			if (std::holds_alternative<int>(left_val) && std::holds_alternative<int>(right_val)) {
				int l = std::get<int>(left_val);
				int r = std::get<int>(right_val);
				return l % r;
			}
		//case'=': {
		//	// 좌변이 변수인지 확인
		//	VariableExpr* var = dynamic_cast<VariableExpr*>(left.get());
		//	if (!var) {
		//		throw std::runtime_error("왼쪽이 이상한 값임");
		//	}

		//	// 오른쪽 값을 왼쪽에 넣기.
		//	Value r;
		//	r.value = right->eval();

		//	if (std::holds_alternative<int>(r.value)) {
		//		r.type = TokenType::IntType;
		//	}
		//	else if (std::holds_alternative<std::string>(r.value)) {
		//		r.type = TokenType::StringType;
		//	}

		//	variables[var->name] = r;
		//	return r.value;
		//}
		default:
			throw std::runtime_error("알수 없는 기호 에러");
		}
		//return;
	}
};