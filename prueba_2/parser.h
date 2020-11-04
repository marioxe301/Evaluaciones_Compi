#ifndef _EXPR_PARSER_H
#define _EXPR_PARSER_H

#include <iosfwd>
#include "lexer.h"

class Parser
{
public:
    Parser(Lexer &lexer): lexer(lexer){}

    void setNextToken();
    void parse();
private:
    Lexer &lexer;
    Token _currentToken;

    void input();
    void stmt_list();
    void stmt_list_p();
    void stmt();
    void arg();
    void expr();
    void expr_p();
    void term();
    void term_p();
    void factor();
    void assign_func_decl();
};

#endif
