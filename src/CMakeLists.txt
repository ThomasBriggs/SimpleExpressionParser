add_library(
    ExpressionParserLib
    Expression.hpp
    Expression.cpp
)

add_executable(main Interactive.cpp)
target_link_libraries(main ExpressionParserLib)
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})