#ifndef __INTERPRETER__
#define __INTERPRETER__ 

#include "ast.h"
#include<unordered_map>
#include <stack>
 
std::unordered_map<std::string,int> typedef VARS;

class Interpreter{
public:
    Interpreter() = default;
    int execute(const ASTNode *root);
private:
    int visit(const NumberExpr * expr);
    int visit(const VariableExpr * expr);

    int visit(const AddExpr * expr);
    int visit(const SubExpr * expr);
    int visit(const MultExpr * expr);
    int visit(const DivExpr * expr);
    int visit(const AndExpr * expr);
    int visit(const OrExpr * expr);
    int visit(const XorExpr * expr);
    int visit(const NotExpr * expr);
    int visit(const ModExpr * expr);
    int visit(const ShlExpr * expr);
    int visit(const ShrExpr * expr);
    int visit(const LessThanExpr * expr);
    int visit(const LessThanEqExpr * expr);
    int visit(const GreaterThanExpr * expr);
    int visit(const GreaterThanEqExpr * expr);
    int visit(const EqualExpr * expr);
    int visit(const DiffExpr * expr);

    //int visit(const StringExpr * expr);
    int visit(const AssignStmt * expr);
    int visit(const PrintStmt * expr);

    int visit(const IfStmt * expr);
    int visit(const WhileStmt * expr);
    int visit(const SeqStmt * expr);
    int visit(const ReadStmt *expr);

    int visit(const FuncDeclStmt *expr);
    int visit(const FuncCallStmt *expr);

    int visit(const ReturnExpr * expr);


private:
    bool isFuctionDefined(const std::string&name);
    void addArgsToStack(const FuncDeclStmt&funct,const std::vector<ExprPtr>&args);
    bool compareArgsSize(const FuncDeclStmt&func,const std::vector<ExprPtr>&args);
    FuncDeclStmt getFunction(const std::string &name) const;
    VARS global_vars;
    std::vector<FuncDeclStmt>functions;
    std::stack<VARS> variable_stack;
};

#endif