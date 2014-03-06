#include <iostream>
#include <typeinfo>

#include "Parser_old.h"

#include "Tokens.h"
#include "Node.h"

using namespace std;

Parser_old::Parser_old()
	: myIndex(0)
	, stackExpr(nullptr)
{
}

vector<Statement*> Parser_old::ParseStmt(std::vector<Token*> tokens, bool multiStmts)
{
	if (myIndex == 0)
	{
		for (int i = 0; i < tokens.size(); ++i)
		{
			if (myIndex % 4 == 3 || true)
				cout << tokens[i]->toString() << "\n";
			else
				cout << tokens[i]->toString() << "\t | \t";
		}
	}

	vector<Statement*> statements;
	Expression *expression = nullptr;

	if (myIndex < tokens.size())
	do
	{
		auto tokenType = typeid(*tokens[myIndex]).hash_code();
		if (tokenType == typeid(TokenText).hash_code())
		{
			TokenText *text = (TokenText*)tokens[myIndex];
			myIndex++;

			if (text->getText() == "print")
			{
				expression = ParseExpr(tokens, myIndex);

				statements.push_back(new StmtPrint(expression));
			}
			else if (text->getText() == "if")
			{
				if (typeid(*tokens[myIndex]) == typeid(TokenOperator))
				{
					TokenOperator* tokenOperator = (TokenOperator*)tokens[myIndex];
					if (tokenOperator->getOperator() != ETokenOperator::LEFTPARENTHESIS)
						break;
				}
				else break;
				std::vector<Statement*> ifStatement;

				myIndex++;

				expression = ParseExpr(tokens, myIndex);

				if (typeid(*tokens[myIndex]) == typeid(TokenOperator))
				{
					TokenOperator* tokenOperator = (TokenOperator*)tokens[myIndex];
					if (tokenOperator->getOperator() != ETokenOperator::RIGHTPARENTHESIS)
						break;
				}
				else break;
				myIndex++;

				ifStatement = ParseStmt(tokens, false);

				// else
				if (typeid(*tokens[myIndex]) == typeid(TokenText))
				{
					TokenText *elseText = (TokenText*)tokens[myIndex];
					if (elseText->getText() == "else")
					{
						statements.push_back(new StmtIfElse((ExprBooleanExpr*)expression, ifStatement, ParseStmt(tokens, false)));
						continue;
					}
				}

				if (dynamic_cast<ExprBooleanExpr*>(expression))
					statements.push_back(new StmtIf((ExprBooleanExpr*)expression, ifStatement));
				else break;
			}
		}
		else if (tokenType == typeid(TokenOperator).hash_code())
		{
			TokenOperator *token = (TokenOperator*)tokens[myIndex];
			switch(token->getOperator())
			{
				case ETokenOperator::SEMICOLON:
					myIndex++;
					if (multiStmts)
						continue;
					else
						return statements;

				case ETokenOperator::LEFTCURLYBRACE:
					{
						myIndex++;
						vector<Statement*> statements2 = ParseStmt(tokens, true);
						statements.reserve(statements.size() + statements2.size());
						statements.insert(statements.end(), statements2.begin(), statements2.end());
					}
					continue;

				case ETokenOperator::RIGHTCURLYBRACE:
					return statements;

			}
		}

		expression = ParseExpr(tokens, myIndex);
	}
	while(myIndex < tokens.size());

	return statements;
}

Expression *Parser_old::ParseExpr(std::vector<Token*> tokens, int index)
{
	Expression *expr = stackExpr;
	myIndex++;

	auto tokenType = &typeid(*tokens[index]);
	if (tokenType == &typeid(TokenInteger))
	{
		TokenInteger *token = (TokenInteger*)tokens[index];

		expr = new ExprInteger(token->getInteger());
	}
	else if (tokenType == &typeid(TokenText))
	{
		TokenText *token = (TokenText*)tokens[index];

		if (token->getText() == "true")
			expr = new ExprBoolean(true);
		else if (token->getText() == "true")
			expr = new ExprBoolean(false);
		else
		{
			//method
		}
	}
	else if (tokenType == &typeid(TokenString))
	{
		TokenString *token = (TokenString*)tokens[index];

		expr = new ExprString(token->getString());
	}
	/*else if (tokenType == &typeid(TokenChar))
	{
		TokenChar *token = (TokenChar*)tokens[index];

		expr = new ExprChar(token->getChar());
	}
	else if (tokenType == &typeid(TokenDouble))
	{
		TokenDouble *token = (TokenDouble*)tokens[index];

		expr = new ExprDouble(token->getDouble());
	}*/
	else if(tokenType == &typeid(TokenOperator))
	{
		TokenOperator *token = (TokenOperator*)tokens[index];
		switch(token->getOperator())
		{
		default:
		case ETokenOperator::SEMICOLON:
			myIndex--;
			return stackExpr;

		case  ETokenOperator::EQUAL:
			{
				Expression *left;
				Expression *right;

				left = stackExpr;
				right = ParseExpr(tokens,myIndex);

				expr = new ExprEqual(left, right);
			}
			break;
		}
	}

	stackExpr = expr;

	if (myIndex < tokens.size()) {
		if (typeid(*tokens[myIndex]) == typeid(TokenOperator))
			return ParseExpr(tokens, myIndex);
	}
	//{
	/*
	Expression *expr2 = ParseExpr(tokens, myIndex);
	if (dynamic_cast<IOperatorExpr*>(expr2))
	return expr2;
	else
	myIndex = index + 1;
	}*/

	return expr;
}

