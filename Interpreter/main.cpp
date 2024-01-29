﻿#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <span>
#include <cassert>
#include <format>

#include "Token/TokenType.hpp"
#include "Token/Token.hpp"
#include "Expr.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "ASTPrinter.hpp"
#include "Lexer.hpp"
#include "Lox.hpp"

int main()
{
	std::cout << "Type \"exit\" to exit the program.\n";
	std::string input;
	while (true)
	{
		std::cout << ">> ";
		std::getline(std::cin, input);
		if (input == "exit")
			break;

		try
		{
			auto tokens = Lexer().lexInput(input);
			Parser parser(tokens);
			auto expr = parser.parse();
			if (expr)
			{
				ASTPrinter().visit(*expr);
				Lox::printInterpretResult(Interpreter().visit(*expr));
			}
		}
		catch (const LexError&)
		{
		}
	} 
	return 0;
}
