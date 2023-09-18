cmake_minimum_required(VERSION 3.0.0)
project(Cave-Swallow VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(Cave-Swallow main.cpp)

target_sources(Cave-Swallow PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/ChessBoard.cpp)

target_include_directories(Cave-Swallow PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
