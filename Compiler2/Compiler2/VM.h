#pragma once
#include <string>
#include <sstream>


typedef char Value;

class VM
{

public:
	void Execute(std::string code);
};