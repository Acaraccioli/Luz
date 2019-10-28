#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <unordered_map>
#include "doctest.h"
#include "expr_lexer.h"

extern std::unordered_map<std::string, int> vars;
ExprLexer yylex;
std::ostringstream sout;

std::vector<TokenInfo> error = {
    std::make_pair(TK_IDENT, "x"),
    std::make_pair(TK_EOF, "EOF")
};

std::vector<TokenInfo> assign = {
    std::make_pair(TK_IDENT, "x"),
    std::make_pair(OP_ASSIGN, "="),
    std::make_pair(TK_OPEN_PAR, "("),
    std::make_pair(TK_NUMBER, "10"),
    std::make_pair(OP_ADD, "+"),
    std::make_pair(TK_NUMBER, "7"),
    std::make_pair(TK_CLOSE_PAR, ")"),
    std::make_pair(OP_MUL, "*"),
    std::make_pair(TK_NUMBER, "5"),
    std::make_pair(TK_EOL, "\\n"),
    std::make_pair(TK_EOF, "EOF")
};

std::vector<TokenInfo> print = {
    std::make_pair(KW_PRINT, "print"),
    std::make_pair(TK_OPEN_PAR, "("),
    std::make_pair(TK_NUMBER, "10"),
    std::make_pair(OP_ADD, "+"),
    std::make_pair(TK_NUMBER, "7"),
    std::make_pair(TK_CLOSE_PAR, ")"),
    std::make_pair(OP_MUL, "*"),
    std::make_pair(TK_NUMBER, "5"),
    std::make_pair(TK_EOL, "\\n"),
    std::make_pair(TK_EOF, "EOF")
};

std::vector<TokenInfo> multiple = {
    std::make_pair(TK_IDENT, "x"),
    std::make_pair(OP_ASSIGN, "="),
    std::make_pair(TK_OPEN_PAR, "("),
    std::make_pair(TK_NUMBER, "10"),
    std::make_pair(OP_ADD, "+"),
    std::make_pair(TK_NUMBER, "7"),
    std::make_pair(TK_CLOSE_PAR, ")"),
    std::make_pair(OP_MUL, "*"),
    std::make_pair(TK_NUMBER, "5"),
    std::make_pair(TK_EOL, "\\n"),
    std::make_pair(KW_PRINT, "print"),
    std::make_pair(TK_IDENT, "x"),
    std::make_pair(TK_EOL, "\\n"),
    std::make_pair(TK_EOF, "EOF")
};

bool throwOnError() 
{
    yylex.setTokenList(error);
    
    bool throwException = false;
    try {
        yyparse();
    } catch (...) {
        throwException = true;
    }
    return throwException;
}

TEST_CASE("Assign statement") {
    REQUIRE(throwOnError());

    sout.str("");
    yylex.setTokenList(assign);

    bool parseSuccess = false;
    try {
        yyparse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(parseSuccess);
    CHECK(vars["x"] == 85);
    CHECK(sout.str().empty());
}

TEST_CASE("Print statement") {
    REQUIRE(throwOnError());

    sout.str("");
    yylex.setTokenList(print);

    bool parseSuccess = false;
    try {
        yyparse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(parseSuccess);
    CHECK(sout.str() == "85");
}

TEST_CASE("Assign/Print") {
    REQUIRE(throwOnError());

    sout.str("");
    yylex.setTokenList(multiple);

    bool parseSuccess = false;
    try {
        yyparse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(parseSuccess);
    CHECK(vars["x"] == 85);
    CHECK(sout.str() == "85");
}
