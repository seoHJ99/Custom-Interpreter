// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

void run(std::string str); 

int main() {
	std::string str1 = "string a = \"HelloWorld\";";
	run(str1);
	std::string str11 = "int a1 = \"HelloWorld\";";
	run(str11);
	std::string str2 = "int b = 1+2*3;";
	run(str2);
	std::string str3 = "string c = 1+2*3;";
	run(str3);
	//std::string str3 = "string function func1 (int c1, int c2){}";
	//run(str3);
	return 0;
}



void run(std::string str) {
	Lexer lexer = Lexer(str);
	Parser parser = Parser(lexer);
	try {
		std::unique_ptr<Expression> expr = parser.parse();
		std::variant<int, std::string> value = expr->eval();
		std::visit([](auto&& v) { // && 만능 참조: 어떤 타입이든 받을수 있음.
			std::cout << "결과: " << v << std::endl;
			}, value);
	}
	catch (std::runtime_error ex) {
		std::cout << "에러: " << ex.what() << std::endl;
	}
}




