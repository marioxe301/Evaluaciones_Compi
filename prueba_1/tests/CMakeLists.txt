cmake_minimum_required (VERSION 3.0)
project (test_lexer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Run FA2LEXER to generate the lexer
add_custom_command (
  OUTPUT const_lexer.cpp
  COMMAND fa2lexer --hdr tokens.h --src const_lexer.cpp --tpl ${PROJECT_SOURCE_DIR}/../DFA/const_lexer.fa2l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../DFA/const_lexer.fa2l
  DEPENDS ${PROJECT_SOURCE_DIR}/../DFA/numeric_constants.jff
          ${PROJECT_SOURCE_DIR}/../DFA/comments.jff
          ${PROJECT_SOURCE_DIR}/../DFA/start.jff
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)
  
add_executable(${PROJECT_NAME}  const_lexer.cpp
                                test_lexer.cpp)
