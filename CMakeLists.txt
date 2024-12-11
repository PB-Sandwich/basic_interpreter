cmake_minimum_required(VERSION 3.30)

project(l)

set(CMAKE_C_COMPILER gcc)
add_compile_options(-ggdb)

add_executable(l src/main.c src/lexer.c src/lexer.h src/parser.c src/parser.h src/interpreter.c src/interpreter.h src/symbol_table.h src/symbol_table.c)
