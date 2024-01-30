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
	auto pos = input.find_first_of(sep, offset);
	assert(pos != std::string_view::npos);
	return std::string(input.begin() + offset, input.begin() + pos);
}

Lexer::Lexer(std::string input) :
	input_(std::move(input)),
	line_count_(1)
{
}

std::vector<Token> Lexer::genTokens()
{
	std::vector<Token> tokens;
	line_count_ = 1;
	constexpr auto delimiter = toChar(TokenType::Eoe);
	static_assert(delimiter.has_value());
	for (const auto& exp : input_ | std::views::split(*delimiter))
	{
		lexInput(tokens, std::string_view(exp.begin(), exp.end()));
		if constexpr (*delimiter == '\n')
		{
			++line_count_;
		}
	}
	return tokens;
}

void Lexer::lexInput(std::vector<Token>& tokens, const std::string_view exp)
{
	const auto isOperatorType = [](TokenType type) -> bool {
		return type == TokenType::Bang ||
			type == TokenType::Div ||
			type == TokenType::Minus ||
			type == TokenType::Mul ||
			type == TokenType::LeftParen ||
			type == TokenType::Plus;
	};

	std::string buf;
	for (size_t i = 0; i < exp.size(); ++i)
	{
		if (std::isdigit(exp[i]) || exp[i] == '.')
		{
			buf.push_back(exp[i]);
			continue;
		}

		if (!buf.empty())
		{
			pushToken(tokens, buf, TokenType::Number);
			buf.clear();
		}

		switch (exp[i])
		{
		case 't': case 'f':
		{
			const auto word = getWord(exp, i);
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
			char c = exp[i];
			++i;
			auto quote = std::find(exp.begin() + i, exp.end(), c);
			if (quote == exp.end())
				throw error(line_count_, std::format("Expect character '{}'", c));
			std::string str(exp.begin() + i, quote);
			i += str.size();
			pushToken(tokens, std::move(str), TokenType::String);
			break;
		}

		default:
			throw error(line_count_, (std::format("Invalid symbol: \'{}\'", exp[i])));
		}
	}

	if (!buf.empty())
		pushToken(tokens, buf, TokenType::Number);

	pushToken(tokens, "", TokenType::Eoe);
}
