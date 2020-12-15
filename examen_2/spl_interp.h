#ifndef __INTER__
#define __INTER__

#include <unordered_map>
#include <vector>
#include "spl_ast.h"

std::unordered_map<std::string,int> typedef Table;

class SplInterp{
public:
    SplInterp() = default;
    std::vector<FuncDecl>functions;
    Table exec(ASTNode *root);
    int executeExpr(ASTNode *expr);
    Table vars;
private:
       int visit(const AssignStmt *a);
       int visit(const AddExpr *a);
       int visit(const DivExpr *a);
       int visit(const MultExpr *a);
       int visit(const SubExpr *a);
       int visit(const EqExpr *a);
       int visit(const DiffExpr *a);
       int visit(const IfStmt *a);
       int visit(const FuncDecl *a);
       int visit(const FuncCall *a);
       int visit(const NumberExpr *a);
       int visit(const VarExpr *a);
       int visit(const SeqStmt *a);
};

#endif