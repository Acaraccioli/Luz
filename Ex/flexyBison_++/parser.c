
void parse(){
    token = yylex();
    int res = M();
    printf("RESULTADO: %d\n", res);
    while(token == TK_SEMICOLON){
        token = yylex();
        if(token != TK_EOF){
            res = M();
            printf("RESULTADO: %d\n", res);
        }
        
    }
    
}

int M(){
    int res = E();
    while(token == TK_RESTA){
        token = yylex();
        res -= E();
    } 
    return res;
}

int E(){
    int res = T();
    while(token == TK_SUMA){
        token = yylex();
        res += T();
    } 
    return res;
}

int T(){
    int res2 = F();
    while(token == TK_MULTI){
        token = yylex();
        res2 *= F();
    }
    return res2;
}

int F(){
    int res3 = 0;
    if(token == TK_LEFTPAR){
        token = yylex();
        res3 = M();
        if(token != TK_RIGHTPAR){
            //error
            //throw std::invalid_argument("Close Parenthesis Not Found");
        } 
        token = yylex();
    } else if(token == TK_NUMBER){
        res3 = atoi(yytext);
        token = yylex();
    } else {
        //error
        //throw std::invalid_argument("Invalid Syntax");
    }
    return res3;
}
