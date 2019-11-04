#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include "doctest.h"
#include "hw.l"

const char *test = "((8+9)-(num1*33))/numero_ddd*money";

TEST_CASE("Lexer") {
    std::istringstream ins;

    ins.str(test);
    Lexer l(ins); 
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
