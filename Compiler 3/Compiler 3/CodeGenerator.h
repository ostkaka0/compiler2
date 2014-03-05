#pragma once

class Expr;

class CodeGenerator
{
	void *GenerateByteCode(Expr *expr);
	void *GenerateBinary(Expr *expr);
};
