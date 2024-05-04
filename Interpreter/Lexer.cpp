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
	lexInput(tokens);
	return tokens;
}

std::optional<char> Lexer::peek(const size_t offset) const
{
	if (offset + 1 >= input_.size())
		return std::nullopt;
	return input_[offset + 1];
}

void Lexer::lexInput(std::vector<Token>& tokens)
{
	std::string buf;
	for (size_t i = 0; i < input_.size(); ++i)
	{
		if (std::isdigit(input_[i]))
		{
			buf.clear();
			while (i < input_.size() && (std::isdigit(input_[i]) || input_[i] == '.'))
			{
				buf.push_back(input_[i]);
				++i;
			}
			--i;
			pushToken(tokens, buf, TokenType::Number);
			continue;
		}

		if (std::isalpha(input_[i]))
		{
			buf.clear();
			while (i < input_.size() && (std::isdigit(input_[i]) || std::isalpha(input_[i])))
			{
				buf.push_back(input_[i]);
				++i;
			}
			--i;
			if (auto it = s_key_words.find(buf); it != s_key_words.end())
				pushToken(tokens, buf, it->second);
			else
				pushToken(tokens, buf, TokenType::Identifier);
			continue;
		}

		switch (input_[i])
		{
		case '>':
			if (auto c = peek(i); c && *c == '=')
			{
				pushToken(tokens, ">=", TokenType::GreaterEq);
				++i;
			}
			else
				pushToken(tokens, ">", TokenType::Greater);
			break;

		case '<':
			if (auto c = peek(i); c && *c == '=')
			{
				pushToken(tokens, "<=", TokenType::LessEq);
				++i;
			}
			else
				pushToken(tokens, "<", TokenType::Less);
			break;

		case '=':
			if (auto c = peek(i); c && *c == '=')
			{
				pushToken(tokens, "==", TokenType::Equal);
				++i;
			}
			else
				pushToken(tokens, "=", TokenType::Assignment);
			break;

		case '!':
			if (auto c = peek(i); c && *c == '=')
			{
				pushToken(tokens, "!=", TokenType::NotEqual);
				++i;
			}
			else 
				pushToken(tokens, "!", TokenType::Bang);
			break;

		case '+':
			pushToken(tokens, "+", TokenType::Plus);
			break;

		case '-':
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
			pushToken(tokens, "", TokenType::Eoe);
			break;

		case ' ': case '\r': case '\0':
			break;

		case '\"': case '\'':
		{
			char c = input_[i];
			++i;
			auto quote = std::find(input_.begin() + i, input_.end(), c);
			if (quote == input_.end())
				throw error(line_count_, std::format("Expect character '{}'", c));
			std::string str(input_.begin() + i, quote);
			i += str.size();
			pushToken(tokens, std::move(str), TokenType::String);
			break;
		}

		default:
			throw error(line_count_, (std::format("Invalid symbol: \'{}\'", input_[i])));
		}
	}

	pushToken(tokens, "", TokenType::Eoe);
}
