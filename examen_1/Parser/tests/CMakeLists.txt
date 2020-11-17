cmake_minimum_required (VERSION 3.0)
project (test_parser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)
  
add_executable(${PROJECT_NAME} 
                    ${PROJECT_SOURCE_DIR}/../expr_parser.cpp
                    test_parser.cpp)
