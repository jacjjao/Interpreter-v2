SET (CMAKE_CXX_STANDARD 20 
     CMAKE_CXX_STANDARD_REQUIRED ON 
     CMAKE_CXX_EXTENSIONS OFF)

add_executable (Interpreter "main.cpp" "Token/TokenType.cpp" "Expression/Expr.cpp")

target_include_directories (Interpreter
PRIVATE
    ${CMAKE_SOURCE_DIR}/Interpreter
)