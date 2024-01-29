#include <iostream>
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
#include "ASTWalker.hpp"
#include "ASTPrinter.hpp"
#include "Lexer.hpp"

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
				std::cout << std::format("{}\n", std::any_cast<double>(ASTWalker().visit(*expr)));
			}
		}
		catch (const LexError& e)
		{
		}
	} 
	return 0;
}
