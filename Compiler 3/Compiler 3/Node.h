#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include "VM.h"

class CodeGenContext;
class Statement;
class Expression;
class VariableDeclaration;

class Node {
public:
    virtual ~Node() {}

	virtual std::string toString() { return " "; }

	bool compare(Token *other) {
		return (typeid(*this).hash_code() == typeid(*other).hash_code());
	}
	//virtual Value* codeGen(CodeGenContext& context) { return nullptr; }
	//virtual Node *Load(std::stringstream &stream) { return nullptr; }
	
};

class Expression : public Node {
public:
	virtual bool equal(Expression *other) {
		return (&typeid(*this) == &typeid(*other));
	}
};

class Statement : public Node {
public:
	virtual void run() {}
};

// Expression types

class ExprBooleanExpr : public Expression {
public:
	virtual bool run()=0;
};

class ExprIntegerExpr : public Expression {
public:
	virtual int run()=0;
};

class ExprStringExpr : public Expression {
public:
	virtual std::string run()=0;
};

class ExprDoubleExpr : public Expression {
public:
	virtual double run()=0;
};

// expressions

class ExprBoolean : public ExprBooleanExpr {
public:
	bool value;
	ExprBoolean(bool value) : value(value) { }
	virtual std::string toString() { return (value)? "true":"false"; }

	virtual bool equal(Expression *other) {
		if (Expression::equal(other))
			return (reinterpret_cast<ExprBoolean*>(other)->value == value);
	}

	virtual bool run() {
		return value;
	}
};

class ExprInteger : public ExprIntegerExpr {
public:
    long long value;
    ExprInteger(long long value) : value(value) { }
	virtual Value* codeGen(CodeGenContext &context) { return nullptr; }
	virtual Node *Load(std::stringstream &stream) { return nullptr; }
	virtual std::string toString() {
		return static_cast<std::ostringstream*>( &(std::ostringstream() << value) )->str();
	}

	virtual bool equal(Expression *other) {
		if (Expression::equal(other))
			return (reinterpret_cast<ExprInteger*>(other)->value == value);
	}

	virtual int run() {
		return value;
	}
    //virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ExprString : public ExprStringExpr {
public:
	std::string value;
	ExprString(std::string value) : value(value) { }
	virtual std::string toString() {
		return value;
	}

	virtual std::string run() {
		return value;
	}
};

class ExprDouble : public ExprDoubleExpr {
public:
    double value;
    ExprDouble(double value) : value(value) { }
    virtual Value* codeGen(CodeGenContext& context) { return nullptr; }
	virtual Node *Load(std::stringstream &stream) { return nullptr; }
	virtual std::string toString() { return static_cast<std::ostringstream*>( &(std::ostringstream() << value) )->str(); }

	virtual bool equal(Expression *other) {
		if (Expression::equal(other))
			return (reinterpret_cast<ExprDouble*>(other)->value == value);
	}

	virtual double run() {
		return value;
	}
};

class IOperatorExpr {
};

class ExprEqual : public ExprBooleanExpr, public IOperatorExpr
{
	Expression *left;
	Expression *right;
public:
	ExprEqual(Expression *left, Expression *right)
		: left(left)
		, right(right) {
	}

	virtual std::string toString() {
		return "equal <expr>(" + left->toString() + "),<expr>(" + right->toString() + ");";
	}

	virtual bool run() {
		return left->equal(right);
	}
};



//////////////		//////////////		//////////////		//////////////		//////////////
//Statements//		//////////////		//////////////		//////////////		//////////////
//////////////		//////////////		//////////////		//////////////		//////////////

/*class Scope : public Statement {

};*/

class StmtIf : public Statement {
public:

	ExprBooleanExpr *exprBooleanExpr;
	std::vector<Statement*> statements;

	StmtIf(ExprBooleanExpr *exprBooleanExpr, std::vector<Statement*> statements)
		: exprBooleanExpr(exprBooleanExpr)
		, statements(statements) {
	}

	virtual std::string toString() {
		std::string str = "if <expr>(" + exprBooleanExpr->toString() + ")";

			for (auto stmt : statements)
				str += ", <stmt>(" + stmt->toString() + ")";

		return str;
	}

	virtual void run() {
		if (exprBooleanExpr->run())
			for (auto stmt : statements)
				stmt->run();
	}

};

class StmtIfElse : public StmtIf {
public:
	std::vector<Statement*> elseStatements;

	StmtIfElse(ExprBooleanExpr *exprBooleanExpr, std::vector<Statement*> statements, std::vector<Statement*> elseStatements)
		: StmtIf(exprBooleanExpr, statements)
		, elseStatements(elseStatements) {
	}

	virtual std::string toString() {
		std::string str = "if <expr>(" + exprBooleanExpr->toString() + ")";

			for (auto stmt : statements)
				str += ", <stmt>(" + stmt->toString() + ")";

			str += "\t else";

			for (auto stmt : elseStatements)
				str += ", <stmt>(" + stmt->toString() + ")";

		return str;
	}

	virtual void run() {
		if (exprBooleanExpr->run()) {
			for (auto stmt : statements)
				stmt->run();
		}
		else {
			for (auto stmt : elseStatements)
				stmt->run();
		}
	}
};

class StmtPrint : public Statement {
public:
	Expression *expr;

	StmtPrint(Expression *expr) : expr(expr) {
	}

	virtual std::string toString() {
		return "print <expr>(" + expr->toString() + ");";
	}

	virtual void run() {
		//auto type = typeid(*expr).hash_code();

		if (dynamic_cast<ExprBooleanExpr*>(expr))
			std::cout << ((((ExprBooleanExpr*)expr)->run())? "true":"false") << std::endl;

		else if (dynamic_cast<ExprIntegerExpr*>(expr))
			std::cout << ((ExprIntegerExpr*)expr)->run() << std::endl;

		else if (dynamic_cast<ExprStringExpr*>(expr))
			std::cout << ((ExprStringExpr*)expr)->run() << std::endl;

		else if (dynamic_cast<ExprDoubleExpr*>(expr))
			std::cout << ((ExprDoubleExpr*)expr)->run() << std::endl;

		else
			std::cerr << "Could not print <expr>(" << expr->toString() << ")!" << std::endl;
	}
};