#!bin/bash

bison --defines=tokens.h -o parser.cpp hw.y
flex -o ../hw.cpp ../hw.l ../parser.cpp ../main.cpp ../expr_ast.h
make
