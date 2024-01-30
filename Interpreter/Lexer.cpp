#include "Lexer.hpp"
#include "Lox.hpp"
#include <format>

void Lexer::pushToken(std::vector<Token>& tokens, std::string str, const TokenType type)
{
	Token token;
	token.str = std::move(str);
	token.type = type;
	token.line = line_count_;
	tokens.push_back(token);
}

LexError Lexer::error(const int line, const std::string& err_msg)
{
	Lox::error(line, err_msg.c_str());
	return LexError(err_msg);
}

std::vector<Token> Lexer::lexInput(std::string_view input)
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
			if (tokens.empty() || (tokens.back().type != TokenType::Number && tokens.back().type != TokenType::String))
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

		case '\n':
			++line_count_;
			break;

		case ' ': case '\r': case '\0':
			break;

		case '\"': case '\'':
		{
			char c = input[i];
			++i;
			auto quote = std::find(input.begin() + i, input.end(), c);
			if (quote == input.end())
				throw error(line_count_, std::format("Expect character '{}'", c));
			std::string str(input.begin() + i, quote);
			i += str.size();
			pushToken(tokens, std::move(str), TokenType::String);
			break;
		}

		default:
			throw error(line_count_, (std::format("Invalid symbol: \'{}\'", input[i])));
		}
	}

	if (!buf.empty())
		pushToken(tokens, buf, TokenType::Number);

	pushToken(tokens, "", TokenType::Eoe);
	++line_count_;

	return tokens;
}
