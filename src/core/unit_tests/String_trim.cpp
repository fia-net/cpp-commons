
#include "gtest/gtest.h"
#include "fianet-core.h"

using namespace Fianet;

namespace {

TEST (StringTest, String_ltrim_works)
{
	EXPECT_EQ (CSTR(""), CSTR("").ltrim());
	EXPECT_EQ (CSTR("abc"), CSTR("abc").ltrim());
	EXPECT_EQ (CSTR("a   abc"), CSTR("a   abc").ltrim());
	EXPECT_EQ (CSTR("abc"), CSTR(" abc").ltrim());
	EXPECT_EQ (CSTR("abc "), CSTR("\t\r\n abc ").ltrim());
	EXPECT_EQ (CSTR("abc"), CSTR("      abc").ltrim());
}

TEST (StringTest, String_rtrim_works)
{
	EXPECT_EQ (CSTR(""), CSTR("").rtrim());
	EXPECT_EQ (CSTR("abc"), CSTR("abc").rtrim());
	EXPECT_EQ (CSTR("a   abc"), CSTR("a   abc").rtrim());
	EXPECT_EQ (CSTR(" abc"), CSTR(" abc").rtrim());
	EXPECT_EQ (CSTR(" abc"), CSTR(" abc ").rtrim());
	EXPECT_EQ (CSTR("abc"), CSTR("abc                     ").rtrim());
	EXPECT_EQ (CSTR("      abc"), CSTR("      abc   ").rtrim());
}

TEST (StringTest, String_trim_works)
{
	EXPECT_EQ (CSTR(""), CSTR("").trim());
	EXPECT_EQ (CSTR("abc"), CSTR("abc").trim());
	EXPECT_EQ (CSTR("a   abc"), CSTR("a   abc").trim());
	EXPECT_EQ (CSTR("abc"), CSTR(" abc").trim());
	EXPECT_EQ (CSTR("abc"), CSTR("abc ").trim());
	EXPECT_EQ (CSTR("abc"), CSTR("    abc").trim());
}

}
