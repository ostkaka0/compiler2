#include "Node.h"

void VM::Execute(Statement *stmt)
{
	stmt->run();
}

void VM::Execute(std::string code)
{

}