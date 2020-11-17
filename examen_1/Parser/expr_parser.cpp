#include "expr_parser.h"

void Parser::parse(){
    setCurretToken(lexer.getNextToken());
    input();
    if(currentToken != Symbol::Eof)throw false;
}
void Parser::setCurretToken(Symbol token){
    currentToken = token;
    switch (token)
    {
    case Symbol::Ident:
        out<<"identifier";
        break;
    case Symbol::Number:
        out<<"number";
        break;
    case Symbol::OpAdd:
        out<<"+";
        break;
    case Symbol::OpAssign:
        out<<"=";
        break;
    case Symbol::OpMul:
        out<<"*";
        break;
    case Symbol::Print:
        out<<"print";
        break;
    case Symbol::OpenPar:
        out<<"(";
        break;
    case Symbol::ClosePar:
        out<<")";
        break;
    case Symbol::Eol:
        out<<";";
        break;
    default:
        break;
    }
}
void Parser::input(){
    list();
    while (currentToken == Symbol::Eol)
    {
        setCurretToken(lexer.getNextToken());
        list();
    }
    
}

void Parser::list(){
    if(currentToken == Symbol::Print){
        setCurretToken(lexer.getNextToken());
        if(currentToken == Symbol::OpenPar){
            setCurretToken(lexer.getNextToken());
            expr();
            if(currentToken == Symbol::ClosePar){
                setCurretToken(lexer.getNextToken());   
            }else{
                throw false;
            }
        }
    }else if(currentToken == Symbol::Ident){
        setCurretToken(lexer.getNextToken());
        if(currentToken == Symbol::OpAssign){
            setCurretToken(lexer.getNextToken());
            expr();
        }else{
            throw false;
        }
    }else{ /*Epsilon*/ }
}
void Parser::expr(){
    term();
    while (currentToken == Symbol::OpAdd)
    {
        setCurretToken(lexer.getNextToken());
        term();
    }
    
}
void Parser::term(){
    factor();
    while (currentToken == Symbol::OpMul)
    {
        setCurretToken(lexer.getNextToken());
        factor();
    }
    
}
void Parser::factor(){
    if(currentToken == Symbol::Number){
        setCurretToken(lexer.getNextToken());
    }else if(currentToken == Symbol::Ident){
        setCurretToken(lexer.getNextToken());
    }else if(currentToken == Symbol::OpenPar){
        setCurretToken(lexer.getNextToken());
        expr();
        if(currentToken == Symbol::ClosePar){
            setCurretToken(lexer.getNextToken());
        }
    }else{
        throw false;
    }
}