#pragma once
#include <string>
#include <vector>
#include <optional>
enum class TokenType {
    // 기본 토큰들
    Number, // 숫자
    Identifier, // 변수명, 함수명, 사용자 정의 이름 등.
    String, // 문자열

    // 함수
    Function, // 함수

    // 연산자들
    Plus,       // +
    Minus,      // -
    Star,       // *
    Slash,      // /
    Percent,  // %
    Assign,     // =

    // 조건 연산자
    And,       // &&
    Or,        // ||

    // 비교 연산자
    Equal,     // ==
    // 대입 연산자
    Is,        // = 

    // 함수 연산자
    Point,     // .

    // 쉼표
    Rest,      // ,

    // 문장 구분
    LParen,     // (
    RParen,     // )
    LBrace,     // {
    RBrace,     // }
    Semicolon,  // ;
    Dquotes,     // "

    StringLiteral, // 문자열

    // 타입
    IntType,     // int
    StringType,  // string

    EndOfFile, // 파일의 끝
    Invalid // 알수 없는 문자열
};

// 토큰 구조체: 토큰 타입과 원본 문자열(text) 저장
struct Token {
    TokenType type;
    std::string text;
};