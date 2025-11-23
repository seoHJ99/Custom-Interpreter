#pragma once
#include "Lexer.h"
#include "Expression.h"
#include "NumberExpr.h"
#include "StringExpr.h"
#include "BinaryExpr.h"
#include "FunctionStruct.h"

class Parser {

public:
	Parser(Lexer& l) : lexer(l)
	{
		current = lexer.getNextToken();
	}

	// 전체 수식 파싱
	std::unique_ptr<Expression> parse() {
		return makeTokenExpr();
	}

private:
	Lexer& lexer; // 현재 토큰 구하는 객체
	Token current; // 현재 보고 있는 토큰

	void consume(TokenType type) {
	
		if (current.type == type) {
			current = lexer.getNextToken(); // 다음 토큰으로 이동
		}
		else
			std::cerr << "Unexpected token: " << current.text << std::endl;
	}


	// factor: 숫자 또는 괄호 수식 처리
	std::unique_ptr<Expression> parseSingleToken() {
		if (current.type == TokenType::Number) {
			int val = std::stoi(current.text); // stoi: 문자열 -> 정수 변환 함수
			consume(TokenType::Number);            // 다음 토큰으로 이동
			return std::make_unique<NumberExpr>(val);
		}
		else if (current.type == TokenType::LParen) {
			consume(TokenType::LParen);
			auto node = makeTokenExpr();                 // 괄호 안 수식 처리
			consume(TokenType::RParen);
			return node;
		}
		else if (current.type == TokenType::StringLiteral) {
			std::string s = current.text;
			consume(TokenType::StringLiteral);
			return std::make_unique<StringExpr>(s);
		}
		else if (current.type == TokenType::Identifier) {
			std::string name = current.text;
			consume(TokenType::Identifier);
			auto node = makeTokenExpr();
			if (current.type == TokenType::Semicolon) {
				variables[name].value =  node->eval();
			}
			return std::make_unique<VariableExpr>(name);
		}
		else if (current.type == TokenType::Is) {
			consume(TokenType::Is);
			auto node = makeTokenExpr();
			return node;
		}
		else if (current.type == TokenType::Dquotes) {
			consume(TokenType::Dquotes);
			auto node = makeTokenExpr();
			return node;
		}
		else if (current.type == TokenType::LBrace) {
			std::string name = current.text;
			consume(TokenType::LBrace);
			auto node = makeTokenExpr();
			if (current.type == TokenType::Semicolon) {
				variables[name].value = node->eval();
			}
		}
		else if (current.type == TokenType::StringType) {
			consume(TokenType::StringType);
			variables[current.text].type = TokenType::StringType;
			auto node = makeTokenExpr();
			auto result = node->eval();
			return node;
		}
		else if (current.type == TokenType::IntType) {
			consume(TokenType::IntType);
			variables[current.text].type = TokenType::IntType;
			auto node = makeTokenExpr();
			return node;
		}
		else if (current.type == TokenType::Function) {
			consume(TokenType::Function);
			auto node = makeTokenExpr();
			return node;
		}
		
		return nullptr;
	}

	// *, / 같은 우선순위 처리 함수
	std::unique_ptr<Expression> highPriority() {
		auto node = parseSingleToken();
		
		while (current.type == TokenType::Star || current.type == TokenType::Slash) {
			char op = current.text[0];   // 연산자
			consume(current.type);       // 다음 토큰으로 이동
			node = std::make_unique<BinaryExpr>(op, std::move(node), parseSingleToken());
		}
		return node;
	}

	// 우선순위가 따로 없는 +, - 처리
	std::unique_ptr<Expression> makeTokenExpr() {
		auto node = highPriority(); 

		while (current.type == TokenType::Plus || current.type == TokenType::Minus) { // 더하기, 빼기
			char op = current.text[0];
			consume(current.type);
			node = std::make_unique<BinaryExpr>(op, std::move(node), highPriority());
		}

		while (current.type == TokenType::Dquotes) { // 문자열
			consume(TokenType::Dquotes);
			node = std::make_unique<StringExpr>(current.text);
		}

		return node;
	}

	void makeMethodParma(FunctionStruct& function) {
		if (current.type == TokenType::LParen) {
			consume(TokenType::LParen);
			
			std::string type;
			if (current.type == TokenType::IntType || current.type == TokenType::StringType) {
				type = current.text;
				consume(current.type);
			}
			else {
				throw std::runtime_error("타입이 뭥미.");
			}

			if (current.type == TokenType::Identifier) {
				function.params[current.text] = type;
				consume(TokenType::Identifier);
			}
			if (current.type == TokenType::Rest) { // 쉼표로 파라미터 여러개 들어오면 전부 재귀로 파라미터로 만들기
				makeMethodParma(function);
				consume(TokenType::Rest);
			}
		}
	}
};