#pragma once
#include <string>
#include <sstream>


typedef char Value;
class Statement;

class VM
{

public:
	void Execute(Statement *stmt);
	void Execute(std::string code);
};