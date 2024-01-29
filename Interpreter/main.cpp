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

void pushToken(std::vector<Token>& tokens, std::string str, const TokenType type)
{
	Token token;
	token.str = std::move(str);
	token.type = type;
	tokens.push_back(token);
}

std::vector<Token> lexInput(const std::string& input)
{
	std::vector<Token> tokens;
	std::string buf;
	for (size_t i = 0; i < input.size(); ++i)
	{
		if (std::isdigit(input[i]) || input[i] == '.')
		{
			buf.push_back(input[i]);
			continue;
		}
		
		if (!buf.empty())
		{
			pushToken(tokens, buf, TokenType::Number);
			buf.clear();
		}

		switch (input[i])
		{
		case '+':
			pushToken(tokens, "+", TokenType::Plus);
			break;

		case '-':
			if (tokens.empty() || tokens.back().type != TokenType::Number)
				pushToken(tokens, "-", TokenType::Negative);
			else
				pushToken(tokens, "-", TokenType::Minus);
			break;

		case '*':
			pushToken(tokens, "*", TokenType::Mul);
			break;

		case '/':
			pushToken(tokens, "/", TokenType::Div);
			break;

		case '(':
			pushToken(tokens, "(", TokenType::LeftParen);
			break;

		case ')':
			pushToken(tokens, ")", TokenType::RightParen);
			break;

		case ' ': case '\r': case '\n':
			break;

		default:
			throw std::invalid_argument("Invalid symbol");
		}
	}

	if (!buf.empty())
	{
		pushToken(tokens, buf, TokenType::Number);
	}

	pushToken(tokens, "", TokenType::Eof);

	return tokens;
}

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
			auto tokens = lexInput(input);
			Parser parser(tokens);
			auto expr = parser.parse();
			if (expr)
			{
				// expr->printTokenInfo(std::cout) << '\n';
				std::cout << std::format("{}\n", expr->evaluate());
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}
	} 
	return 0;
}
