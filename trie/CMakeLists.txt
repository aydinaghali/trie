cmake_minimum_required(VERSION 3.15)
project(trie)

set(SOURCES src/main.cpp src/Trie.cpp)
#AUX_SOURCE_DIRECTORY(src SOURCES)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

