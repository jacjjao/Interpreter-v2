#include "pch.hpp"
#include "Lexer.hpp"
#include "Lox.hpp"

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

std::string Lexer::getWord(const std::string_view input, const size_t offset, const char sep)
{
	size_t i = offset + 1;
	assert(i <= input.size());
	for (; i < input.size() && input[i] != sep; ++i)
		;
	return std::string(input.begin() + offset, input.begin() + i);
}

std::vector<Token> Lexer::lexInput(const std::string_view input)
{
	const auto isOperatorType = [](TokenType type) -> bool {
		return type == TokenType::Bang ||
			type == TokenType::Div ||
			type == TokenType::Minus ||
			type == TokenType::Mul ||
			type == TokenType::LeftParen ||
			type == TokenType::Plus;
	};

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
		case 't': case 'f':
		{
			const auto word = getWord(input, i);
			const auto it = s_key_words.find(word);
			if (it != s_key_words.end())
			{
				i += word.size();
				pushToken(tokens, word, it->second);
			}
			break;
		}

		case '!':
			pushToken(tokens, "!", TokenType::Bang);
			break;

		case '+':
			pushToken(tokens, "+", TokenType::Plus);
			break;

		case '-':
			if (tokens.empty() || isOperatorType(tokens.back().type))
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
