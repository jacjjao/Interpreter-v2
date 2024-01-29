#include "Lexer.hpp"
#include "Lox.hpp"
#include <format>
#include <sstream>

void Lexer::pushToken(std::vector<Token>& tokens, std::string str, const TokenType type)
{
	Token token;
	token.str = std::move(str);
	token.type = type;
	tokens.push_back(token);
}

LexError Lexer::error(const int line, const std::string& err_msg)
{
	Lox::error(line, err_msg.c_str());
	return LexError(err_msg);
}

std::vector<Token> Lexer::lexInput(const std::string& input)
{
	std::vector<Token> tokens;
	std::string line;
	std::stringstream ss(input);
	int line_count = 0;
	while (std::getline(ss, line))
	{
		std::string buf;
		for (size_t i = 0; i < line.size(); ++i)
		{
			if (std::isdigit(line[i]) || line[i] == '.')
			{
				buf.push_back(line[i]);
				continue;
			}

			if (!buf.empty())
			{
				pushToken(tokens, buf, TokenType::Number);
				buf.clear();
			}

			switch (line[i])
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
				throw error(line_count, (std::format("Invalid symbol: \'{}\'", line[i])));
			}
		}

		if (!buf.empty())
			pushToken(tokens, buf, TokenType::Number);
		++line_count;
	}

	pushToken(tokens, "", TokenType::Eof);

	return tokens;
}
