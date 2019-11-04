#!bin/bash

re2c -o expr_lexer.cpp expr_lexer.re

g++ -o expr_lexer expr_lexer.cpp main.cpp

