
#include "gtest/gtest.h"
#include "fianet-core.h"

using namespace Fianet;

namespace {


TEST (XStringTest, XString_ltrim_works)
{
	EXPECT_EQ (CSTR("").ltrim(), CSTR(""));
	EXPECT_EQ (CSTR("abc").ltrim(), CSTR("abc"));
	EXPECT_EQ (CSTR("a   abc").ltrim(), CSTR("a   abc"));
	EXPECT_EQ (CSTR(" abc").ltrim(), CSTR("abc"));
	EXPECT_EQ (CSTR("\t\r\n abc ").ltrim(), CSTR("abc "));
	EXPECT_EQ (CSTR("      abc").ltrim(), CSTR("abc"));
}

TEST (XStringTest, XString_rtrim_works)
{
	EXPECT_EQ (XString("").rtrim(), CSTR(""));
	EXPECT_EQ (XString("abc").rtrim(), CSTR("abc"));
	EXPECT_EQ (XString("a   abc").rtrim(), CSTR("a   abc"));
	EXPECT_EQ (XString(" abc").rtrim(), CSTR(" abc"));
	EXPECT_EQ (XString(" abc ").rtrim(), CSTR(" abc"));
	EXPECT_EQ (XString("abc                     ").rtrim(), CSTR("abc"));
	EXPECT_EQ (XString("      abc   ").rtrim(), CSTR("      abc"));
}

TEST (XStringTest, XString_trim_works)
{
	EXPECT_EQ (XString("").trim(), CSTR(""));
	EXPECT_EQ (XString("abc").trim(), CSTR("abc"));
	EXPECT_EQ (XString("a   abc").trim(), CSTR("a   abc"));
	EXPECT_EQ (XString(" abc").trim(), CSTR("abc"));
	EXPECT_EQ (XString("abc ").trim(), CSTR("abc"));
	EXPECT_EQ (XString("    abc").trim(), CSTR("abc"));
}

}
