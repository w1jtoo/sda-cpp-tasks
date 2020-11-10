#include "entry_point.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

static NotationConstants constants = NotationConstants();
static Tokenizer tokenizer = Tokenizer(constants);
static ReverseNotationEvaluator convertor = ReverseNotationEvaluator(constants);
static ReveseNotationParser parser = ReveseNotationParser(constants);

namespace Example
{
	TEST(Public, MyTest1)
	{
		ASSERT_EQ(.0, evaluate("0"));
	}

	TEST(Public, TokenizerTests)
	{
		std::vector<std::string> empty;
		ASSERT_EQ(empty, tokenizer.tokenize(" "));
	}

	TEST(Public, TokenizerTests1)
	{
		std::vector<std::string> nonempty;
		nonempty.push_back("1");
		nonempty.push_back("+");
		nonempty.push_back("2");
		nonempty.push_back("-");
		nonempty.push_back("3");
		ASSERT_EQ(nonempty, tokenizer.tokenize("1 + 2-3"));
	}

	TEST(Public, TokenizerTests11)
	{
		std::vector<std::string> nonempty;
		nonempty.push_back("1");
		nonempty.push_back("-");
		nonempty.push_back("2");
		nonempty.push_back("+");
		nonempty.push_back("31");
		ASSERT_EQ(nonempty, tokenizer.tokenize("1-2+31"));
	}

	TEST(Public, TokenizerMultipleOperations)
	{
		std::vector<std::string> nonempty;
		nonempty.push_back("1");
		nonempty.push_back("+");
		nonempty.push_back("sin");
		nonempty.push_back("(");
		nonempty.push_back("2");
		nonempty.push_back(")");
		nonempty.push_back("-");
		nonempty.push_back("(");
		nonempty.push_back("3");
		nonempty.push_back(")");
		ASSERT_EQ(nonempty, tokenizer.tokenize("1 + sin( 2)-(3 )"));
	}

	TEST(Public, FunctionalTests)
	{
		ASSERT_EQ(3, evaluate("1 + 2"));
	}

	TEST(Public, 1FunctionalTests)
	{
		ASSERT_EQ(3, evaluate("1*2+1"));
	}

} // namespace Example
