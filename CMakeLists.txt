cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(subgraph-isomophism-CUDA)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(externals/matrix_reader)
add_subdirectory(externals/fmt)

add_executable(${PROJECT_NAME} src/main.cu src/graph/graph.c 
                src/match/iso.c src/match/sub-iso.c 
                src/match/match.cu src/parsing/parser.c 
                src/time.cu src/utils/utis.cu)
target_link_libraries(${PROJECT_NAME}  fmt MatrixMarketReader)


