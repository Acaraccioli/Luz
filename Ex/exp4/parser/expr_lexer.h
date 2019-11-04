#ifndef _LEXER_H
#define _LEXER_H
#include <iostream>
#include <fstream>
#include <string>
#include "./build/expr_tokens.h"
#include <vector>
using TokenInfo = std::pair<int, double>;

class ExprLexer {
public:
    ExprLexer() { }

    void setTokenList(const std::vector<TokenInfo>& _tklst) {
        tklist = _tklst;
        it = tklist.begin();
    }

    int operator()() {
        if (it == tklist.end()) {
            return 0;
        }
        int tk = it->first;
        yylval = it->second;
        it++;
        
        return tk;
    }
    
    bool hasTokens() { return it != tklist.end(); }

private:
    std::vector<TokenInfo> tklist;
    std::vector<TokenInfo>::iterator it;
};
#endif
