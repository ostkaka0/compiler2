#ifdef VILL_ANVÄNDA_KOD
#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include "VM.h"

class CodeGenContext;
class NodeStatement;
class NodeExpression;
class NodeVariableDeclaration;

typedef std::vector<NodeStatement*> StatementList_;
typedef std::vector<NodeExpression*> ExpressionList_;
typedef std::vector<NodeVariableDeclaration*> VariableList_;

class Node {
public:
    virtual ~Node() {}
	virtual Value* codeGen(CodeGenContext& context) { return nullptr; }
	virtual Node *Load(std::stringstream &stream) { return nullptr; }
};

class NodeExpression : public Node {
};

class NodeStatement : public Node {
};

class NodeInteger : public NodeExpression {
public:
    long long value;
    NodeInteger(long long value) : value(value) { }
	virtual Value* codeGen(CodeGenContext &context);
	virtual Node *Load(std::stringstream &stream);
    //virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NodeDouble : public NodeExpression {
public:
    double value;
    NodeDouble(double value) : value(value) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NodeIdentifier : public NodeExpression {
public:
    std::string name;
    NodeIdentifier(const std::string& name) : name(name) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NodeExpressionList : public NodeExpression
{
public:
	ExpressionList_ expressions;

	NodeExpressionList(ExpressionList_ expressions)
		: expressions(expressions)
	{
	}

};

class NodeMethodCall : public NodeExpression {
public:
    const NodeIdentifier& id;
    NodeExpressionList arguments;
    NodeMethodCall(const NodeIdentifier& id, NodeExpressionList& arguments) :
        id(id), arguments(arguments) { }
    NodeMethodCall(const NodeIdentifier& id) : id(id) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NodeBinaryOperator : public NodeExpression {
public:
    int op;
    NodeExpression& lhs;
    NodeExpression& rhs;
    NodeBinaryOperator(NodeExpression& lhs, int op, NodeExpression& rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NodeAssignment : public NodeExpression {
public:
    NodeIdentifier& lhs;
    NodeExpression& rhs;
    NodeAssignment(NodeIdentifier& lhs, NodeExpression& rhs) : 
        lhs(lhs), rhs(rhs) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NodeBlock : public NodeExpression {
public:
    NodeStatementList statements;
    NodeBlock() { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NodeExpressionStatement : public NodeStatement {
public:
    NodeExpression& expression;
    NodeExpressionStatement(NodeExpression& expression) : 
        expression(expression) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NodeVariableDeclaration : public NodeStatement {
public:
    const NodeIdentifier& type;
    NodeIdentifier& id;
    NodeExpression *assignmentExpr;
    NodeVariableDeclaration(const NodeIdentifier& type, NodeIdentifier& id) :
        type(type), id(id) { }
    NodeVariableDeclaration(const NodeIdentifier& type, NodeIdentifier& id, NodeExpression *assignmentExpr) :
        type(type), id(id), assignmentExpr(assignmentExpr) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};

class NodeFunctionDeclaration : public NodeStatement {
public:
    const NodeIdentifier& type;
    const NodeIdentifier& id;
    NodeVariableList arguments;
    NodeBlock& block;
    NodeFunctionDeclaration(const NodeIdentifier& type, const NodeIdentifier& id, 
            const NodeVariableList& arguments, NodeBlock& block) :
        type(type), id(id), arguments(arguments), block(block) { }
    virtual Value* codeGen(CodeGenContext& context);
	virtual Node *Load(std::stringstream &stream);
};
#endif