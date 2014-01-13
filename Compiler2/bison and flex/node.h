#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include "VM.h"//#include <neko_vm.h>//#include <llvm/Value.h>

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NVariableDeclaration*> VariableList;

class Node {
public:
    virtual ~Node() {}
	virtual Value* codeGen(CodeGenContext& context) { return nullptr; }
	virtual Node *Load(std::stringstream &stream) { return nullptr; }
};

class NExpression : public Node {
};

class NStatement : public Node {
};

class NInteger : public NExpression {
public:
    long long value;
    NInteger(long long value) : value(value) { }
	virtual Value* codeGen(CodeGenContext &context);
	virtual Node *Load(std::stringstream &stream);
    //virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NDouble : public NExpression {
public:
    double value;
    NDouble(double value) : value(value) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NMethodCall : public NExpression {
public:
    const NIdentifier& id;
    ExpressionList arguments;
    NMethodCall(const NIdentifier& id, ExpressionList& arguments) :
        id(id), arguments(arguments) { }
    NMethodCall(const NIdentifier& id) : id(id) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NBinaryOperator : public NExpression {
public:
    int op;
    NExpression& lhs;
    NExpression& rhs;
    NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NAssignment : public NExpression {
public:
    NIdentifier& lhs;
    NExpression& rhs;
    NAssignment(NIdentifier& lhs, NExpression& rhs) : 
        lhs(lhs), rhs(rhs) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NBlock : public NExpression {
public:
    StatementList statements;
    NBlock() { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) : 
        expression(expression) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NVariableDeclaration : public NStatement {
public:
    const NIdentifier& type;
    NIdentifier& id;
    NExpression *assignmentExpr;
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id) :
        type(type), id(id) { }
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id, NExpression *assignmentExpr) :
        type(type), id(id), assignmentExpr(assignmentExpr) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NFunctionDeclaration : public NStatement {
public:
    const NIdentifier& type;
    const NIdentifier& id;
    VariableList arguments;
    NBlock& block;
    NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id, 
            const VariableList& arguments, NBlock& block) :
        type(type), id(id), arguments(arguments), block(block) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};