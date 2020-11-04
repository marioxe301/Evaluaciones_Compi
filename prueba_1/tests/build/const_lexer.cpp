#include "const_lexer.h"

enum class State {
    start_q0,
    Numeric_Constants_q0,
    Numeric_Constants_q1,
    Numeric_Constants_q10,
    Numeric_Constants_q3,
    Numeric_Constants_q6,
    Numeric_Constants_q8,
    Comments_q0,
    Comments_q1,
    Comments_q2,
    Comments_q3,
    Comments_q5,
    Comments_q6,
    Comments_q7,
    Comments_q8,
};

Token ConstLexer::getNextToken()
{
    text = "";
    State state = State::start_q0;
    int ch = getNextChar();

    while (true) {
        switch (state) {
            // start
            case State::start_q0:
                if ((ch == '\n') || (ch == ' ')) {
                    state = State::start_q0;
                    ch = getNextChar();
                }
                else if (ch == EOF) {
                    text += ch;
                    return Token::Eof;
                }
                else {
                    // Trying next automaton 'Numeric_Constants
                    state = State::Numeric_Constants_q0;
                }
                break;
            // Numeric_Constants
            case State::Numeric_Constants_q0:
                if (((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <= 'f'))) {
                    text += ch;
                    state = State::Numeric_Constants_q8;
                    ch = getNextChar();
                }
                else if ((ch == '1') || (ch == '0')) {
                    text += ch;
                    state = State::Numeric_Constants_q1;
                    ch = getNextChar();
                }
                else {
                    state = State::Numeric_Constants_q10;
                }
                break;
            case State::Numeric_Constants_q1:
                if ((ch == '0') || (ch == '1')) {
                    text += ch;
                    state = State::Numeric_Constants_q1;
                    ch = getNextChar();
                }
                else if ((ch >= '2') && (ch <= '7')) {
                    text += ch;
                    state = State::Numeric_Constants_q3;
                    ch = getNextChar();
                }
                else if ((ch == 'b') || (ch == 'B')) {
                    text += ch;
                    return Token::Binary;
                }
                else {
                    ungetChar(ch);
                    return Token::Decimal;
                }
                break;
            case State::Numeric_Constants_q10:
                if ((ch >= '0') && (ch <= '7')) {
                    text += ch;
                    state = State::Numeric_Constants_q3;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'Comments
                    state = State::Comments_q0;
                }
                break;
            case State::Numeric_Constants_q3:
                if ((ch == 'o') || (ch == 'O')) {
                    text += ch;
                    return Token::Octal;
                }
                else if ((ch >= '0') && (ch <= '7')) {
                    text += ch;
                    state = State::Numeric_Constants_q3;
                    ch = getNextChar();
                }
                else if ((ch >= '8') && (ch <= '9')) {
                    text += ch;
                    state = State::Numeric_Constants_q6;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'Comments
                    state = State::Comments_q0;
                }
                break;
            case State::Numeric_Constants_q6:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Numeric_Constants_q6;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Decimal;
                }
                break;
            case State::Numeric_Constants_q8:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')) || ((ch >= 'A') && (ch <= 'F'))) {
                    text += ch;
                    state = State::Numeric_Constants_q8;
                    ch = getNextChar();
                }
                else if ((ch == 'h') || (ch == 'H')) {
                    text += ch;
                    return Token::Hex;
                }
                else {
                    // Trying next automaton 'Comments
                    state = State::Comments_q0;
                }
                break;
            // Comments
            case State::Comments_q0:
                if (ch == '(') {
                    state = State::Comments_q1;
                    ch = getNextChar();
                }
                else if (ch == '#') {
                    state = State::Comments_q2;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::Comments_q1:
                if (ch == '*') {
                    state = State::Comments_q5;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::Comments_q2:
                if ((ch == '_') || (ch == ' ') || ((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9'))) {
                    state = State::Comments_q3;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::Comments_q3:
                if ((ch == '_') || (ch == ' ') || ((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'Z'))) {
                    state = State::Comments_q3;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    state = State::start_q0;
                }
                break;
            case State::Comments_q5:
                if ((ch == ' ') || (ch == '\n') || ((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'z'))) {
                    state = State::Comments_q6;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::Comments_q6:
                if ((ch == '\n') || (ch == ' ') || ((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'Z'))) {
                    state = State::Comments_q6;
                    ch = getNextChar();
                }
                else if (ch == '*') {
                    state = State::Comments_q7;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::Comments_q7:
                if (ch == ')') {
                    state = State::Comments_q8;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::Comments_q8:
                ungetChar(ch);
                state = State::start_q0;
                break;
        }
    }

}

const char *ConstLexer::tokenToString(Token tk)
{
    switch (tk) {
        case Token::Octal: return "Octal";
        case Token::Hex: return "Hex";
        case Token::Decimal: return "Decimal";
        case Token::Eof: return "Eof";
        case Token::Binary: return "Binary";
        default: return "Unknown";
    }
    
}