#pragma once
#include <string>
#include <iostream>
#include "TokenType.h"

class Lexer {

public:
	Lexer(const std::string& src) : src(src), pos(0) {}
	Token getNextToken();  // 선언만
	Token stringLiteral();
	//Token variableName(int);

private:
	std::string src;
	size_t pos; // 문자열 인덱스

	void skipWhitespace() {
		while (pos < src.size() && std::isspace(src[pos])) {
			pos++;
		}
	}
};

Token Lexer::getNextToken() {
	skipWhitespace();
	if (pos >= src.size())  return Token{ TokenType::EndOfFile, "\0" };

	char now = src[pos];
	char next;
	int type = -1;

	if (pos + 1 < src.size()) {
		next = src[pos + 1];
	}

	if (pos+9 < src.size() && src.substr(pos, 9) == "function ") {
		std::string name;
		pos = pos + 9;

		while (pos < src.size()) {
			char c = src[pos]; // 현재 글자

			if (isspace(static_cast<unsigned char>(c))) {  //빈값이면 나가기
				break;
			}

			name.push_back(c); // 문자열 누적
			pos++;
		}

		return Token{ TokenType::Function, name };
	}

	if (pos+4 < src.size() && src.substr(pos, 4) == "int ") {
		pos += 4;
		return Token{TokenType::IntType, "int"};
	}

	if (pos + 7 < src.size() && src.substr(pos, 7) == "string ") {
		pos += 7;
		return Token{ TokenType::StringType, "string" };
	}

	if (std::isdigit(now)) {
		std::string num;
		while (pos < src.size() && std::isdigit(src[pos])) {
			num += src[pos++]; // 숫자 하나씩 읽기
		}
		return Token{ TokenType::Number, num };
	}

	if (std::isalpha(now)) { // 알파벳으로 시작하면 이름이라고 인식하기
		skipWhitespace();

		std::string name;

		while (pos < src.size()) {
			char c = src[pos]; // 현재 글자

			if (isspace(static_cast<unsigned char>(c))) {  //빈값이면 나가기
				break;
			}

			name.push_back(c); // 문자열 누적
			pos++;
		}

		return Token{ TokenType::Identifier, name };
	}


	if (now == '=' && next == '=') {
		pos++;
		return Token{ TokenType::Equal, "==" };
	}


	if (now == '=') {
		pos++;
		return Token{ TokenType::Is, "=" };
	}

	if (now == '+') {
		pos++;
		return Token{ TokenType::Plus, "+" };
	}

	if (now == '-') {
		pos++;
		return Token{ TokenType::Minus, "-" };
	}

	if (now == '/') {
		pos++;
		return Token{ TokenType::Slash, "/" };
	}

	if (now == '*') {
		pos++;
		return Token{ TokenType::Star, "*" };
	}

	if (now == '%') {
		pos++;
		return Token{ TokenType::Percent, "%" };
	}

	if (now == '.') {
		pos++;
		return Token{ TokenType::Point, "." };
	}

	if (now == '&' && next == '&') {
		pos++;
		return Token{ TokenType::And, "&&" };
	}

	if (now == '|' && next == '|') {
		pos++;
		return Token{ TokenType::Or, "||" };
	}

	if (now == '(') {
		pos++;
		return Token{ TokenType::LParen, "(" };
	}

	if (now == ')') {
		pos++;
		return Token{ TokenType::RParen, ")" };
	}

	if (now == ';') {
		pos++;
		return Token{ TokenType::Semicolon, ";" };
	}

	if (now == '\0') {
		pos++;
		return Token{ TokenType::EndOfFile, "\0" };
	}

	if (now == '"' || now == '\"') {
		return stringLiteral();
	}

	if (now == '{') {
		pos++;
		return Token{ TokenType::LBrace, "{" };
	}

	if (now == '{') {
		pos++;
		return Token{ TokenType::LBrace, "}" };
	}

	if (now == ',') {
		pos++;
		return Token{ TokenType::Rest, ","};
	}

	return Token{ TokenType::Invalid, std::string(1, now) };
}


Token Lexer::stringLiteral() {
	pos++; // 처음 " 건너뛰기
	size_t start = pos;

	while (pos < src.size() && src[pos] != '"') {
		pos++;
	}

	std::string s = src.substr(start, pos - start);

	pos++; // 닫는 " 건너뛰기
	return Token{ TokenType::StringLiteral, s };
}
