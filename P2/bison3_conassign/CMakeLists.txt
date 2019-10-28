cmake_minimum_required (VERSION 3.0)
project (test_flexer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FLEX "flex")
set(BISON "bison")

add_custom_command (
    OUTPUT gramatica.c
    COMMAND ${FLEX} -o ./gramatica.c ../gramatica.l ../main.cpp ../parser.cpp
    MAIN_DEPENDENCY ../gramatica.l ../parser.cpp
  )
add_custom_command (
    OUTPUT tokens.h  expr_parser.cpp
    COMMAND ${BISON} --defines=../tokens.h -o ../expr_parser.cpp ../ejemplobison.y
    MAIN_DEPENDENCY ../ejemplobison.y
  )
 

include_directories(${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)

add_executable(${PROJECT_NAME} 
./gramatica.c ./main.cpp ./expr_parser.cpp)