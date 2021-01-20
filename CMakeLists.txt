cmake_minimum_required(VERSION 3.0.0)
project(ExpressionParser VERSION 0.1.0)

include(CTest)
enable_testing()

set(LIB ExpressionParserLib)

add_subdirectory(src)
add_subdirectory(test)