cmake_minimum_required (VERSION 3.0)
project (cfg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)

add_executable(${PROJECT_NAME}  ../expr_CFG.h ../x86_asmgen.cpp ../x86_asmgen.h ../main.cpp)
