﻿SET (CMAKE_CXX_STANDARD 20 
     CMAKE_CXX_STANDARD_REQUIRED ON 
     CMAKE_CXX_EXTENSIONS OFF)

add_executable (Interpreter "main.cpp" "Token/TokenType.cpp" "Expr.cpp" "Parser.cpp" "Lox.cpp" "Interpreter.cpp" "ASTPrinter.cpp" "Lexer.cpp" "Environment.cpp")

target_precompile_headers(${PROJECT_NAME}
	PRIVATE
		pch.hpp
)

target_include_directories (Interpreter
PRIVATE
    ${CMAKE_SOURCE_DIR}/Interpreter
)