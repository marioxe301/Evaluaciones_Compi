#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include "doctest.h"
#include "const_lexer.h"

const char *test = "deadbeefh\n"
                    "12345678 # Line comment 1\n"
                    "1010b (* Line 1 \n"
                    "Line 2 *) 7654o\n"
                    "# Line Comment 2";

doctest::String toString(Token tk)
{
    switch (tk)
    {
        case Token::Decimal: return "Decimal";
        case Token::Hex: return "Hex";
        case Token::Binary: return "Binary";
        case Token::Octal: return "Octal";
        case Token::Eof: return "Eof";
        default:
            return "Unknown";
    }
}

TEST_CASE("Lexer")
{
    std::istringstream ins;

    ins.str(test);
    ConstLexer l(ins);

    CHECK(l.getNextToken() == Token::Hex);
    CHECK(l.getText() == "deadbeefh");
    CHECK(l.getNextToken() == Token::Decimal);
    CHECK(l.getText() == "12345678");
    CHECK(l.getNextToken() == Token::Binary);
    CHECK(l.getText() == "1010b");
    CHECK(l.getNextToken() == Token::Octal);
    CHECK(l.getText() == "7654o");
    CHECK(l.getNextToken() == Token::Eof);
}
