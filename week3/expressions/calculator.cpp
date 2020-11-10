/*
 * =====================================================================================
 *
 *		 Filename:	calculator.cpp
 *
 *	  Description:
				I don't want create new files, sorry =(
 *
 *		  Created:	11/01/2020 02:41:43 PM
 *		 Compiler:	gcc
 *
 *		   Author:	w1jtoo
 *
 * =====================================================================================
 */

#include "calculator.h"
/* ================================================================================= */
/* ============================= NotationConstants ================================= */
/* ================================================================================= */

bool NotationConstants::is_digit(const std::string &str)
{
	if (str[0] == '-')
		return str.find_first_not_of("1234567890.", 1) == std::string::npos;
	else
		return str.find_first_not_of("1234567890.", 0) == std::string::npos;
}

bool NotationConstants::is_operator(const std::string &str)
{
	return std::find(operators.begin(),
					 operators.end(), str) != operators.end();
}

bool NotationConstants::is_trigo(const std::string &str)
{
	return std::find(trigonometric.begin(),
					 trigonometric.end(), str) != trigonometric.end();
}

NotationConstants::NotationConstants()
{
	operators = {
		"+", "*", "/", "^", "(", ")", "deg", "rad", "ln", "lg", "-", "sin",
		"cos", "tan", "cotan", "asin", "acos", "atan", "acot", "sqrt"};

	trigonometric = {"asin", "acos", "atan", "acot"};

	priority = {
		{"+", 1},
		{"-", 1},
		{"*", 2},
		{"/", 2},
		{"^", 3},
		{"sin", 4},
		{"cos", 4},
		{"tan", 4},
		{"cotan", 4},
		{"asin", 4},
		{"acos", 4},
		{"atan", 4},
		{"acot", 4},
		{"sqrt", 4},
		{"ln", 4},
		{"lg", 4}};

	constants = {
		{"pi", "3.14159265358979323846"},
		{"e", "2.71828182845904523536"}};
}

/* ================================================================================= */
/* =================================== Tokenizer =================================== */
/* ================================================================================= */

Tokenizer::Tokenizer(const NotationConstants constants)
{
	_constants = constants;
}

std::vector<std::string> Tokenizer::tokenize(const std::string &str)
{
	std::stringstream ss(str);
	std::string item;
	std::vector<std::string> splitted_tokens;
	std::vector<std::string> tokens;
	std::vector<std::string> result_tokens;

	while (std::getline(ss, item, ' '))
	{
		if (item.empty() || item == " " || item == "\t")
			continue;

		splitted_tokens.push_back(item);
	}

	for (const auto &word : splitted_tokens)
	{
		size_t i = 1, start_index = 0;
		while (start_index + i <= word.length())
		{
			const auto substr = word.substr(start_index, i);
			if (_constants.is_digit(substr) || _constants.is_trigo(substr) || _constants.is_operator(substr))
			{
				tokens.push_back(substr);
				start_index += i;
				i = 1;
			}
			else
				++i;
		}
	}

	if (tokens.size() == 0)
		return result_tokens;

	result_tokens.push_back(result_tokens[0]);

	for (size_t i = 1; i < tokens.size(); i++)
	{
		if (_constants.is_digit(tokens[i - 1]) && _constants.is_digit(tokens[i]))
		{
			result_tokens[i - 1] += result_tokens[i];
		}
		result_tokens.push_back(tokens[i - 1]);
	}

	return result_tokens;
}
/* ================================================================================= */
/* ================================== Validator ==================================== */
/* ================================================================================= */

Validator::Validator(const NotationConstants constants)
{
	_constants = constants;
}

bool Validator::is_valid_bracket_squence(const std::string &expr)
{
	int brackets = 0;
	for (const char &i : expr)
	{
		if (i == '(')
			brackets++;
		if (i == ')')
			brackets--;
		if (brackets < 0)
			return false;
	}
	return (brackets == 0);
}

std::string Validator::remove_spaces(const std::string &str)
{
	std::string exprWithoutExtra = str;
	size_t pos = exprWithoutExtra.find("  ", 0);
	while (pos != std::string::npos)
	{
		exprWithoutExtra.erase(pos, 1);
		pos = exprWithoutExtra.find("  ", pos);
	}

	if (str.front() == ' ')
		exprWithoutExtra.erase(0, 1);
	if (str.back() == ' ')
		exprWithoutExtra.pop_back();

	return exprWithoutExtra;
}

void Validator::ensure_valid_format(const std::string &str)
{
	if (!is_valid_bracket_squence(str))
	{
		throw std::runtime_error("Error in brackets");
	}

	std::istringstream ss(str);
	while (ss)
	{
		std::string word;
		ss >> word;
		if (word.empty())
			break;
		if (!_constants.is_operator(word) && !_constants.is_digit(word))
		{
			throw std::runtime_error("There are invalid characters");
		}
	}
}

/* ================================================================================= */
/* ============================= ReveseNotationParser ============================== */
/* ================================================================================= */

ReveseNotationParser::ReveseNotationParser(const NotationConstants constants)
{
	_constants = constants;
}

std::vector<std::string> ReveseNotationParser::to_polish_notation(const std::vector<std::string> &tokens)
{
	std::vector<std::string> polish;
	std::vector<std::string> op;
	std::string last;
	bool fixDigit = false;

	for (auto &token : tokens)
	{
		auto word = token;
		if (word.empty())
			break;

		if (word == "-" && (last.empty() || _constants.is_operator(last)))
		{
			fixDigit = true;
			continue;
		}

		if (fixDigit && _constants.is_digit(word))
		{
			word.insert(0, "-");
			fixDigit = false;
		}

		if (!_constants.is_operator(word))
			polish.push_back(word);
		else
		{
			if (!op.empty())
			{
				if (word == "(")
					op.push_back(word);
				else if (word == ")")
				{
					while (op.back() != "(" && !op.empty())
					{
						polish.push_back(op.back());
						op.pop_back();
					}
					op.pop_back();
				}
				else
				{
					while (!op.empty() && _constants.priority[op.back()] >= _constants.priority[word])
					{
						polish.push_back(op.back());
						op.pop_back();
					}
					op.push_back(word);
				}
			}
			else
				op.push_back(word);
		}

		last = word;
	}

	polish.insert(polish.end(), op.rbegin(), op.rend());
	return polish;
}

/* ================================================================================= */
/* =========================== ReverseNotationEvaluator ============================ */
/* ================================================================================= */

double ReverseNotationEvaluator::to_result(const std::vector<std::string> &notation)
{
	std::vector<double> answer;

	for (const std::string &str : notation)
	{
		if (!_constants.is_operator(str))
			answer.push_back(stof(str));
		else
		{
			if (str == "*")
			{
				if (answer.size() < 2)
				{
					throw std::runtime_error("Not enough operands for the * operator");
				}
				answer.push_back(answer[answer.size() - 2] * answer.back());
				answer.erase(answer.end() - 3, answer.end() - 1);
			}
			if (str == "/")
			{
				if (answer.size() < 2)
				{
					throw std::runtime_error("Not enough operands for the / operator");
				}
				if (answer[answer.size() - 1] == 0)
				{
					throw std::runtime_error("Division by zero");
				}
				answer.push_back(answer[answer.size() - 2] / answer.back());
				answer.erase(answer.end() - 3, answer.end() - 1);
			}
			if (str == "+")
			{
				if (answer.size() < 2)
				{
					throw std::runtime_error("Not enough operands for the + operator");
				}
				answer.push_back(answer[answer.size() - 2] + answer.back());
				answer.erase(answer.end() - 3, answer.end() - 1);
			}
			if (str == "-")
			{
				if (answer.size() < 2)
				{
					throw std::runtime_error("Not enough operands for the - operator");
				}
				answer.push_back(answer[answer.size() - 2] - answer.back());
				answer.erase(answer.end() - 3, answer.end() - 1);
			}
			if (str == "^")
			{
				if (answer.size() < 2)
				{
					throw std::runtime_error("Not enough operands for the ^ operator");
				}
				answer.push_back(pow(answer[answer.size() - 2], answer[answer.size() - 1]));
				answer.erase(answer.end() - 3, answer.end() - 1);
			}
			if (str == "sin")
			{
				if (answer.empty())
				{
					throw std::runtime_error("sin has no parameter");
				}
				answer.push_back(std::sin(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "cos")
			{
				if (answer.empty())
				{
					throw std::runtime_error("cos has no parameter");
				}
				answer.push_back(std::cos(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "tan")
			{
				if (answer.empty())
				{
					throw std::runtime_error("tan has no parameter");
				}
				answer.push_back(std::tan(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "cotan")
			{
				if (answer.empty())
				{
					throw std::runtime_error("cotan has no parameter");
				}
				answer.push_back(1 / std::tan(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "asin")
			{
				if (answer.empty())
				{
					throw std::runtime_error("asin has no parameter");
				}
				answer.push_back(std::asin(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "acos")
			{
				if (answer.empty())
				{
					throw std::runtime_error("acos has no parameter");
				}
				answer.push_back(std::acos(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "atan")
			{
				if (answer.empty())
				{
					throw std::runtime_error("atan has no parameter");
				}
				answer.push_back(std::atan(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "acot")
			{
				if (answer.empty())
				{
					throw std::runtime_error("acot has no parameter");
				}
				answer.push_back(1 / std::atan(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "sqrt")
			{
				if (answer.empty())
				{
					throw std::runtime_error("sqrt has no parameter");
				}
				answer.push_back(std::sqrt(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "ln")
			{
				if (answer.empty())
				{
					throw std::runtime_error("ln has no parameter");
				}
				answer.push_back(std::log(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
			if (str == "lg")
			{
				if (answer.empty())
				{
					throw std::runtime_error("lg has no parameter");
				}
				answer.push_back(std::log10(answer[answer.size() - 1]));
				answer.erase(answer.end() - 2);
			}
		}
	}

	// if (std::isnan(answer[0]))
	// return "NaN";

	std::stringstream ss;
	ss << answer[0];
	// return ss.str() + ((isTrigo(notation.back())) ? " rad" : "");
	return answer[0];
}

ReverseNotationEvaluator::ReverseNotationEvaluator(const NotationConstants constants)
{
	_constants = constants;
}

double ReverseNotationEvaluator::solve(std::vector<std::string> expression)
{
	return to_result(expression);
}

/* ================================================================================= */
/* =================================== evaluate ==================================== */
/* ================================================================================= */

static NotationConstants constants = NotationConstants();
static Tokenizer tokenizer = Tokenizer(constants);
static Validator validator = Validator(constants);
static ReverseNotationEvaluator convertor = ReverseNotationEvaluator(constants);
static ReveseNotationParser parser = ReveseNotationParser(constants);

double evaluate(std::string expression)
{
	validator.ensure_valid_format(expression);

	auto tokens = tokenizer.tokenize(expression);
	auto expr = parser.to_polish_notation(tokens);
	return convertor.solve(expr);
}
