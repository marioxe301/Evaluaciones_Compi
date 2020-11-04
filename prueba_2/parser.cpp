#include "parser.h"

// Main functions

void Parser::setNextToken(){
    _currentToken = lexer.getNextToken();
}
void Parser::parse(){
    setNextToken();
    input();
    if( _currentToken != Token::Eof) throw false;
}

// Grammar Productions
void Parser::input(){
    stmt_list();
}
void Parser::stmt_list(){
    stmt();
    stmt_list_p();
}
void Parser::stmt_list_p(){
    if(_currentToken == Token::Semicolon){
        setNextToken();
        stmt();
        if(_currentToken == Token::Semicolon){
            setNextToken();
            stmt_list_p();
        }else{
            throw false;
        }
    }else{}

}
void Parser::stmt(){
    if(_currentToken == Token::Ident){
        setNextToken();
        if(_currentToken == Token::OpAssign){
            setNextToken();
            expr();
        }else if(_currentToken == Token::OpenPar){
            setNextToken();
            arg();
            if(_currentToken == Token::ClosePar){
                setNextToken();
                if(_currentToken == Token::OpAssign){
                    setNextToken();
                    expr();
                }else{
                    throw false;
                }
            }else{
                throw false;
            }
        }
    }else if(_currentToken == Token::KwPrint){
        setNextToken();
        expr();
    }else{
        throw false;
    }
}
void Parser::arg(){
    if(_currentToken == Token::Number){
        setNextToken();
    }else if( _currentToken == Token::Ident){
        setNextToken();
    }else{
        throw false;
    }
}
void Parser::expr(){
    term();
    expr_p();
}
void Parser::expr_p(){
    if(_currentToken == Token::OpAdd){
        setNextToken();
        term();
        expr_p();
    }else if(_currentToken == Token::OpSub){
        setNextToken();
        term();
        expr_p();
    }else{/*Epsilon*/}
}
void Parser::term(){
    factor();
    term_p();
}
void Parser::term_p(){
    if(_currentToken == Token::OpMul){
        setNextToken();
        factor();
        term_p();
    }else{/*Epsilon*/}
}
void Parser::factor(){
    if(_currentToken == Token::Ident){
        setNextToken();
    }else if(_currentToken == Token::Number){
        setNextToken();
    }else if(_currentToken == Token::OpenPar){
        setNextToken();
        expr();
        if(_currentToken == Token::ClosePar){
            setNextToken();
        }else{
            throw false;
        }
    }else{
        throw false;
    }
}