#include "lexer.h"

/*!fa2lexer
    %option generate.tokens = true;
    %file "start.jff";
    %file "comments.jff";
    %file "constants.jff";
    %file "identifiers.jff";
    %file "operators.jff";

    %token.descriptions{
        Identifier = "Indentifier",
        KwContinue = "Keyword Continue",
        KwRead = "Keyword Read",
        KwTo = "Keyword To",
        KwProc = "Keyword Procedure",
        KwFunc = "Keyword Function",
        KwProgram = "Keyword Program",
        KwVar = "Keyword Variable",
        KwArray = "Keyword Array",
        KwOf = "Keyword Of",
        KwInteger = "Keyword Integer",
        KwBool = "Keyword Boolean",
        KwChar = "Keyword Character",
        KwNot = "Keyword Not",
        KwAnd = "Keyword And",
        KwOr = "Keyword Or",
        KwXor = "Keyword XOR",
        KwShl = "Keyword Shift Left",
        KwShr = "Keyword Shift Right",
        KwDiv = "Keyword Division",
        KwMod = "Keyword Modular",
        KwBeg = "Keyword Begin",
        KwEnd = "Keyword End",
        KwBreak = "Keyword Break",
        KwIf = "Keyword If",
        KwThen = "Keyword Then",
        KwElse = "Keyword Else",
        KwWhile = "Keyword While",
        KwRepeat = "Keyword Repeat",
        KwUntil = "Keyword Until",
        KwFor = "Keyword For",
        KwDo = "Keyword Do",
        KwPrint = "Keyword Write",
        KwPrintLn = "Keyword Writeln",
        OpenBracket = "Open Bracket Operator",
        CloseBracket = "Close Bracket Operator",
        Coma = "Coma Operator",
        SemiColon = "SemiColon Operator",
        Equal = "Equal Operator",
        Minus = "Minus Operator",
        DoublePoint = "Double Point Operator",
        Plus = "Plus Operator",
        Mult = "Multiplication Operator",
        LessThan = "Less than Operator",
        GreaterThan = "Greater than Operator",
        Different = "Different Operator",
        LessThanEq = "Less than equal Operator",
        GreaterThanEq = "Greater than equal Operator",
        Dot = "Dot Operator",
        Assign = "Assign Operator",
        Colon = "Color Operator",
        OpenParen = "Open Parenthesis",
        CloseParen = "Close Parenthesis",
        StringConst = "String Constant",
        CharConst = "Char Constant",
        BoolConst = "Bool Constant",
        Unknown = "Unknwon Token"
    }

    %generate.state_enum(State);
*/

Token Lexer::findStringConst(std::string &str){
    return str.size() == 1 ? Token::CharConst : Token::StringConst;
}

Token Lexer::findOperator(std::string &str){
    if(str == "["){
        return Token::OpenBracket;
    }else if(str == "]"){
        return Token::CloseBracket;
    }else if(str == ","){
        return Token::Coma;
    }else if(str == ";"){
        return Token::SemiColon;
    }else if(str == "="){
        return Token::Equal;
    }else if(str == "-"){
        return Token::Minus;
    }else if(str == "+"){
        return Token::Plus;
    }else if(str == "*"){
        return Token::Mult;
    }else if(str == "<"){
        return Token::LessThan;
    }else if(str == ">"){
        return Token::GreaterThan;
    }else if(str == "<="){
        return Token::LessThanEq;
    }else if(str == ">="){
        return Token::GreaterThanEq;
    }else if(str == "<>"){
        return Token::Different;
    }else if(str == "."){
        return Token::Dot;
    }else if(str == ":="){
        return Token::Assign;
    }else if(str == ":"){
        return Token::Colon;
    }else if(str == "("){
        return Token::OpenParen;
    }else if(str == ")"){
        return Token::CloseParen;
    }else if(str == ".."){
        return Token::DoublePoint;
    }else{
        return Token::Unknown;
    }
}

void Lexer::setLineNumber(char t){
    t == '\n' ? line++ : line = line;
}
std::string Lexer::getLineNumber(){
    return std::to_string(line);
}

void Lexer::preprocessorCheck(){
    getNextToken();
    if(text == "ifdef"){
        getNextToken();
        if(text == "nanopascal"){
            isDefine.push(true);
            getNextChar();
        }else{
            // consumria todo los caracteres hasta llegar a un ;
            isDefine.push(false);
            int ch = getNextChar();
            while(ch != '{'){
                ch = getNextChar();
            }
            ungetChar(0);
        }
    }else if(text == "else"  && isDefine.top()){
        int ch = getNextChar();
        while(ch != '{'){
            ch = getNextChar();
        }
        ungetChar(0);
        //getNextChar();
    }else if( text == "else" && !isDefine.top()){
        getNextChar();
    }else if( text == "endif"){
        isDefine.pop();
        getNextChar();
    }else{
        reportErrorInPreprocessor();
    }
    return;
}

Token Lexer::findKeyWord(std::string &str){

    std::for_each(str.begin(),str.end(),[](char &c){
        c = ::tolower(c);
    });


    if(str == "program"){
        return Token::KwProgram;
    }else if(str == "var"){
        return Token::KwVar;
    }else if(str == "array"){
        return Token::KwArray;
    }else if(str == "of"){
        return Token::KwOf;
    }else if(str == "integer"){
        return Token::KwInteger;
    }else if(str == "boolean"){
        return Token::KwBool;
    }else if(str == "char"){
        return Token::KwChar;
    }else if(str == "not"){
        return Token::KwNot;
    }else if(str == "and"){
        return Token::KwAnd;
    }else if(str == "or"){
        return Token::KwOr;
    }else if(str == "xor"){
        return Token::KwXor;
    }else if(str == "shl"){
        return Token::KwShl;
    }else if(str == "shr"){
        return Token::KwShr;
    }else if(str == "div"){
        return Token::KwDiv;
    }else if(str == "mod"){
        return Token::KwMod;
    }else if(str == "begin"){
        return Token::KwBeg;
    }else if(str == "end"){
        return Token::KwEnd;
    }else if(str == "break"){
        return Token::KwBreak;
    }else if(str == "if"){
        return Token::KwIf;
    }else if(str == "then"){
        return Token::KwThen;
    }else if(str == "else"){
        return Token::KwElse;
    }else if(str == "while"){
        return Token::KwWhile;
    }else if(str == "repeat"){
        return Token::KwRepeat;
    }else if(str == "until"){
        return Token::KwUntil;
    }else if(str == "for"){
        return Token::KwFor;
    }else if(str == "do"){
        return Token::KwDo;
    }else if(str == "write"){
        return Token::KwPrint;
    }else if(str == "writeln"){
        return Token::KwPrintLn;
    }else if(str == "function"){
        return Token::KwFunc;
    }else if(str == "procedure"){
        return Token::KwProc;
    }else if(str == "read"){
        return Token::KwRead;
    }else if(str == "true" || str == "false"){
        return Token::BoolConst;   
    }else if(str == "continue"){
        return Token::KwContinue;
    }else if(str == "to"){
        return Token::KwTo;
    }
    else{
        return Token::Identifier;
    }
}

Token Lexer::getNextToken()
{
    text = "";
/*!fa2lexer
    %generate.lexer(text);
*/
}

const char *Lexer::tokenToString(Token tk)
{
/*!fa2lexer
    %generate.toString(tk);
*/    
}
