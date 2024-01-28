#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <span>
#include <cassert>

#include "Token/TokenType.hpp"
#include "Token/Token.hpp"
#include "Expression/Expr.hpp"

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

	return tokens;
}

std::unique_ptr<Expr> parseTokens(std::span<Token> tokens);

std::unique_ptr<Expr> parseNumber(const Token& token)
{
	return std::unique_ptr<Expr>(new NumberExpr(token));
}

std::unique_ptr<Expr> parseTerm(std::span<Token> tokens) // '+' '-'
{
	assert(tokens.size() <= std::numeric_limits<int>::max());
	for (int i = tokens.size() - 1; i >= 0; --i)
		if (tokens[i].type == TokenType::Plus || tokens[i].type == TokenType::Minus)
		{
			auto expr = std::make_unique<BinaryExpr>(tokens[i]);
			expr->lhs = parseTokens(std::span<Token>(tokens.begin(), tokens.begin() + i));
			expr->rhs = parseTokens(std::span<Token>(tokens.begin() + i + 1, tokens.end()));
			return std::unique_ptr<Expr>(expr.release());
		}
	return nullptr;
}

std::unique_ptr<Expr> parseFactor(std::span<Token> tokens) // '*' '/'
{
	assert(tokens.size() <= std::numeric_limits<int>::max());
	for (int i = tokens.size() - 1; i >= 0; --i)
		if (tokens[i].type == TokenType::Mul || tokens[i].type == TokenType::Div)
		{
			auto expr = std::make_unique<BinaryExpr>(tokens[i]);
			expr->lhs = parseTokens(std::span<Token>(tokens.begin(), tokens.begin() + i));
			expr->rhs = parseTokens(std::span<Token>(tokens.begin() + i + 1, tokens.end()));
			return std::unique_ptr<Expr>(expr.release());
		}
	return nullptr;
}

std::unique_ptr<Expr> parseUnary(std::span<Token> tokens)
{
	assert(tokens.size() <= std::numeric_limits<int>::max());
	for (int i = tokens.size() - 1; i >= 0; --i)
		if (tokens[i].type == TokenType::Negative)
		{
			auto expr = std::make_unique<UnaryExpr>(tokens[i]);
			expr->rhs = parseTokens(std::span<Token>(tokens.begin() + i + 1, tokens.end()));
			return std::unique_ptr<Expr>(expr.release());
		}
	return nullptr;
}

std::unique_ptr<Expr> parseTokens(std::span<Token> tokens)
{
	if (tokens.empty())
		return nullptr;

	auto expr = parseTerm(tokens);
	if (expr)
		return expr;

	expr = parseFactor(tokens);
	if (expr)
		return expr;

	expr = parseUnary(tokens);
	if (expr)
		return expr;

	assert(tokens.size() == 1);
	return parseNumber(tokens[0]);
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
		auto tokens = lexInput(input);
		auto expr = parseTokens(tokens);
		if (expr)
		{
			// expr->printTokenInfo(std::cout) << '\n';
			std::cout << "value = " << expr->evaluate() << '\n';
		}
		else
			std::cout << "Invalid or empty expression!\n";
	} 
	return 0;
}
