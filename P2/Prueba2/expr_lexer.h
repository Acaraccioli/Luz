#ifndef _ExprLexer_H
#define _ExprLexer_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include "expr_tokens.h"

using TokenInfo = std::pair<int, std::string>;

#define TK_EOF 0

class ExprLexer {
public:
    int intVal;
    std::string strVal;
    std::string idval;
	ExprLexer() {}

    void setTokenList(const std::vector<TokenInfo>& tklst) {
        tklist = tklst;
        it = tklist.begin();
    }

    int getLineNo() { return 1; }

    int operator()() {
        int tk = it->first;

        if (tk == TK_NUMBER) {
            intVal = std::strtol(it->second.c_str(), nullptr, 10);
        } else if(tk == TK_IDENT){
            strVal = strdup(it->second.c_str());
            idval = strVal;
        } else {
            strVal = strdup(it->second.c_str());
        }
        
        if (it != tklist.end()) {
            it++;
        }
        
        return tk;
    }
    
    bool hasTokens() { return it != tklist.end(); }

private:
    std::vector<TokenInfo> tklist;
    std::vector<TokenInfo>::iterator it;
};
#endif
