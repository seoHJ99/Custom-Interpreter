#pragma once
#include <unordered_map>
#include <string>
#include "ClassStruct.h"

std::unordered_map<std::string, ClassStruct> classes;


class ClassRepository {

public:
	void save(std::string name, ClassStruct classStruct);
	ClassStruct get(std::string name);

	void save(std::string name, ClassStruct classStruct) {
		classes[name] = classStruct;
	}

	ClassStruct get(std::string name) {
		return classes[name];
	}
};