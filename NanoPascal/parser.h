#ifndef __PARSER__
#define __PARSER__

#include "ast.h"
#include "test_defines.h"
#include "lexer.h"

#define HANDLE_ERROR(m) throw std::string(m)
#define OUT(m) std::cout<<m<<std::endl

class Parser{
public:
    Parser(const Lexer&lexer)
    :lexer(lexer)
    {}
    void setCurrentToken(){
        currentTokenType = lexer.getNextToken();
        currentToken = lexer.getText();
    }
    
    bool isSameToken(const Token &token){
        return currentTokenType == token;
    }

    void parse();
private:

    Lexer lexer;
    Token currentTokenType;
    std::string currentToken;
    std::vector<StmtPtr>seq;

private:

    void program();
    void VariableSection();
    void VariableDecl();
    void Type();
    void ArrayBody();
    void SubprogramDecl();
    void SubprogramHeader();
    void FunctionBody();
    void ProcedureBody();
    void FunctOrProcArgs();
    void ArgumentBodyVar();
    void ArgumentBodyId();
    void Statement();
    void ElseStmt();
    void Block();
    void AssignOrSubProg();
    void AssignOrSubProgP();
    void IoBody();
    void Argument();
    void AssignFor();
    void ArrayVar();
    void FuncArgs();
    void Expr();
    void Rel();
    void Term();
    void Neg();
    void Factor();
};

#endif