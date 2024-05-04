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
	Interpreter env;
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
			auto exprs = parser.parse();
			for (auto& expr : exprs) {
				env.interpret(*expr);
			}
		}
		catch (const LexError&)
		{
		}
		catch (const std::runtime_error& e)
		{
			fprintf(stderr, "Runtime error %s\n", e.what());
		}
	}
}

void fileMode(const std::filesystem::path& path)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		Interpreter env;

		file.open(path);
		std::stringstream ss;
		ss << file.rdbuf();
		Lexer lexer(std::move(ss).str());

		auto tokens = lexer.genTokens();

		Parser parser(tokens);
		auto exprs = parser.parse();
		for (auto& expr : exprs) {
			env.interpret(*expr);
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
