#include <stdio.h>
#include <iostream>
void yyparse();
int main()
{
    try
    {
    yyparse();
    }
    catch( std::string& e) {
        std::cout << e<<std::endl;
    }
    return 0;
}