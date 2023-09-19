cmake_minimum_required(VERSION 3.14)
project(isomorphism)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(externals/matrix_reader)
add_subdirectory(externals/fmt)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}  fmt MatrixMarketReader)