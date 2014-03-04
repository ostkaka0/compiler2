#include <queue>

class Parser
{
	Expr *ParseExpr(std::queue<Token*> *tokens);
	Stmt *ParseStmt(std::queue<Token*> *tokens);
}