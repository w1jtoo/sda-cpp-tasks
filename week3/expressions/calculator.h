/*
 * =====================================================================================
 *
 *		 Filename:	calculator.cpp
 *
 *	  Description:	
 *
 *		  Created:	11/01/2020 02:42:38 PM
 *		 Compiler:	gcc
 *
 *		   Author:	w1jtoo
 *
 * =====================================================================================
 */
#include <variant>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
#include <iostream>

/* ================================================================================= */
/* ============================= NotationConstants ================================= */
/* ================================================================================= */
class NotationConstants
{
public:
	NotationConstants();

	bool is_digit(const std::string &str);
	bool is_operator(const std::string &str);
	bool is_trigo(const std::string &str);

	std::vector<std::string> operators;
	std::vector<std::string> trigonometric;
	std::map<std::string, int> priority;
	std::map<std::string, std::string> constants;
};

/* ================================================================================= */
/* =================================== Tokenizer =================================== */
/* ================================================================================= */
class Tokenizer
{
private:
	NotationConstants _constants;

public:
	Tokenizer(const NotationConstants constants);
	std::vector<std::string> tokenize(const std::string &str);
};

/* ================================================================================= */
/* ================================== Validator ==================================== */
/* ================================================================================= */
class Validator
{
private:
	NotationConstants _constants;
	std::string remove_spaces(const std::string &str);
	bool is_valid_bracket_squence(const std::string &expr);

public:
	Validator(const NotationConstants constants);
	void ensure_valid_format(const std::string &str);
};

/* ================================================================================= */
/* ============================= ReveseNotationParser ============================== */
/* ================================================================================= */
class ReveseNotationParser
{
private:
	std::string remove_spaces(const std::string &str);
	void check_expression(const std::string &expr);
	bool is_valid_bracket_squence(const std::string &expr);
	std::string get_correct_expression(const std::string &expr);
	// std::vector<std::string> to_polish_notation(const std::string &expr);
	NotationConstants _constants;

public:
	ReveseNotationParser(const NotationConstants constants);
	std::vector<std::string> to_polish_notation(const std::vector<std::string> &tokens);
};

/* ================================================================================= */
/* =========================== ReverseNotationEvaluator ============================ */
/* ================================================================================= */
class ReverseNotationEvaluator
{
private:
	NotationConstants _constants;
	double to_result(const std::vector<std::string> &Notation);

public:
	ReverseNotationEvaluator(const NotationConstants constants);
	double solve(std::vector<std::string> expression);
};

double evaluate(std::string expression);
