cmake_minimum_required (VERSION 2.6)
project (test_hw)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14")

# Run flex to generate the lexer
add_custom_command (
  OUTPUT ../expr_lexer.cpp
  COMMAND flex -o ../expr_lexer.cpp ../expr_lexer.l 
  MAIN_DEPENDENCY ../expr_lexer.l 
)

# Run bison to generate the parser
add_custom_command (
  OUTPUT ../expr_parser.cpp ../tokens.h
  COMMAND bison -o ../expr_parser.cpp -rall --defines=../expr_tokens.h ../expr_parser.y 
  MAIN_DEPENDENCY ../expr_parser.y 
)

#Run TreeCC to generate the AST Definition
add_custom_command (
  OUTPUT ../expr_ast.cpp
  COMMAND treecc -o expr_ast.cpp -e cpp -h expr_ast.h ../ast.tc
  MAIN_DEPENDENCY ../ast.tc
)


include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(main ../expr_parser.cpp ../expr_lexer.cpp ../expr_ast.cpp ../main.cpp)
