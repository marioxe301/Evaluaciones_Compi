#ifndef _PARSER_H
#define _PARSER_H

#include <iosfwd>
#include "expr_lexer.h"

class Parser
{
public:
    Parser(Lexer& lexer, std::ostream& out): lexer(lexer), out(out)
    {}

    void parse();
    void setCurretToken(Symbol token);

private:
    Lexer& lexer;
    std::ostream& out;
    Symbol currentToken;

    void input();
    void list();
    void expr();
    void term();
    void factor();
};

#endif
