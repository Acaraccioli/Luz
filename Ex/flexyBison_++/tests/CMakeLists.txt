cmake_minimum_required (VERSION 2.6)
project (test_hw)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14")

# Run flex to generate the lexer
add_custom_command (
  OUTPUT ../hw.cpp
  COMMAND flex -o ../hw.cpp ../hw.l 
  MAIN_DEPENDENCY ../hw.l 
)

# Run bison to generate the parser
add_custom_command (
  OUTPUT ../parser.cpp ../tokens.h
  COMMAND bison -o ../parser.cpp -rall --defines=../tokens.h ../hw.y 
  MAIN_DEPENDENCY ../hw.y 
)


include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(test_hw ../parser.cpp ../hw.cpp ../expr_ast.h ../main.cpp)
