#include "pch.hpp"
#include "Token/TokenType.hpp"
#include "Token/Token.hpp"
#include "Expr.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "ASTPrinter.hpp"
#include "Lexer.hpp"
#include "Lox.hpp"

void cmdMode()
{
	std::cout << "Type \"exit\" to exit the program.\n";
	while (true)
	{
		std::string input;
		std::cout << ">> ";
		std::getline(std::cin, input);
		if (input == "exit")
			break;

		try
		{
			auto tokens = Lexer(std::move(input)).genTokens();
			for (const auto& token : tokens)
				std::cout << std::format("{} ", toString(token.type));
			std::cout << '\n';
			Parser parser(tokens);
			auto expr = parser.parse();
			if (expr)
			{
				ASTPrinter().print(*expr);
				Lox::printInterpretResult(Interpreter().interpret(*expr));
			}
		}
		catch (const LexError&)
		{
		}
	}
}

void fileMode(const std::filesystem::path& path)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		file.open(path);
		std::stringstream ss;
		ss << file.rdbuf();
		Lexer lexer(std::move(ss).str());
		auto tokens = lexer.genTokens();
		auto expr_begin = tokens.begin();
		while (expr_begin != tokens.end())
		{
			auto expr_end = std::find_if(expr_begin + 1, tokens.end(), [](const Token& t) -> bool { return t.type == TokenType::Eoe; });
			if (expr_end == tokens.end())
				return;
			++expr_end; // Inorder to include the Eof token
			Parser parser(std::span(expr_begin, expr_end));
			auto expr = parser.parse();
			if (expr)
			{
				ASTPrinter().print(*expr);
				Lox::printInterpretResult(Interpreter().interpret(*expr));
				if (Lox::hadRuntimeErr())
					return;
			}
			expr_begin = expr_end;
		}
	}
	catch (const LexError&)
	{
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << std::format("Error when read the file: {}\n", e.what());
	}
}

int main(int argc, char** argv)
{
	if (argc <= 1)
		cmdMode();
	else if (argc == 2)
		fileMode(argv[1]);
	else
	{
		std::cout << "Usage: .\\interpreter.exe [file.txt]\n";
	}

	return 0;
}
