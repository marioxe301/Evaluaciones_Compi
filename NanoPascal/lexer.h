#ifndef __LEXER_H__
#define __LEXER_H__

#include "tokens.h"
#include <iostream>
#include <string>
#include <istream>
#include <algorithm>
#include <stack>

class Lexer{
public:
    Lexer(std::istream &input): input(input){
        line = 1;
    }
    
    std::string getText(){ return text; }
    int getNextChar(){ return input.get();}
    void ungetChar(int ch){ input.unget();}
    void reportError(int ch){
        throw std::string("Unexpected error");
    }

    void reportErrorInPreprocessor(){
        throw std::string("Unexpected error in preprocessor");
    }

    Token getNextToken();
    Token findOperator(std::string &str);
    Token findKeyWord(std::string &str);
    Token findStringConst(std::string &str);
    static const char *tokenToString(Token tk);
    void setLineNumber(char t);
    std::string getLineNumber();
    void preprocessorCheck();
    
private:
    std::string text;
    std::istream &input;
    int line;
    std::stack<bool>isDefine;
};


#endif