
#include "gtest/gtest.h"
#include "fianet-core.h"

using namespace Fianet;

namespace {

TEST (StringTest, String_indexofchar_works)
{
	EXPECT_EQ(-1, CSTR("").indexOfChar('a'));
	EXPECT_EQ(-1, CSTR("abc").indexOfChar('\0'));
	EXPECT_EQ(-1, CSTR("").indexOfChar('\0'));

	EXPECT_EQ(2, CSTR("abc").indexOfChar('c'));
	EXPECT_EQ(0, CSTR("abc").indexOfChar('a'));
	EXPECT_EQ(-1, CSTR("abc").indexOfChar('d'));
	EXPECT_EQ(0, CSTR("aa").indexOfChar('a'));
	EXPECT_EQ(0, CSTR("abcabca").indexOfChar('a'));
	EXPECT_EQ(2, CSTR("abcabca").indexOfChar('c'));
}

TEST (StringTest, String_lastindexofchar_works)
{
	EXPECT_EQ(-1, CSTR("").lastIndexOfChar('a'));
	EXPECT_EQ(-1, CSTR("abc").lastIndexOfChar('\0'));
	EXPECT_EQ(-1, CSTR("").lastIndexOfChar('\0'));

	EXPECT_EQ(2, CSTR("abc").lastIndexOfChar('c'));
	EXPECT_EQ(0, CSTR("abc").lastIndexOfChar('a'));
	EXPECT_EQ(-1, CSTR("abc").lastIndexOfChar('d'));
	EXPECT_EQ(1, CSTR("aa").lastIndexOfChar('a'));
	EXPECT_EQ(6, CSTR("abcabca").lastIndexOfChar('a'));
	EXPECT_EQ(5, CSTR("abcabca").lastIndexOfChar('c'));
}

TEST (StringTest, String_indexof_works)
{
	EXPECT_EQ(-1, CSTR("").indexOf(CSTR("abc")));
	EXPECT_EQ(-1, CSTR("abc").indexOf(CSTR("")));
	EXPECT_EQ(-1, CSTR("").indexOf(CSTR("")));

	EXPECT_EQ(3, CSTR("abcABC").indexOf(CSTR("ABC")));
	EXPECT_EQ(0, CSTR("abcabc").indexOf(CSTR("ab")));
	EXPECT_EQ(0, CSTR("abcabcabc").indexOf(CSTR("abc")));
	EXPECT_EQ(-1, CSTR("abcabc").indexOf(CSTR("abd")));
	EXPECT_EQ(2, CSTR("ababcab").indexOf(CSTR("abc")));
	EXPECT_EQ(2, CSTR("ABABAC").indexOf(CSTR("ABAC")));
}

TEST (StringTest, String_lastindexof_works)
{
	EXPECT_EQ(-1, CSTR("").lastIndexOf(CSTR("abc")));
	EXPECT_EQ(-1, CSTR("abc").lastIndexOf(CSTR("")));
	EXPECT_EQ(-1, CSTR("").lastIndexOf(CSTR("")));

	EXPECT_EQ(3, CSTR("abcABC").lastIndexOf(CSTR("ABC")));
	EXPECT_EQ(3, CSTR("abcabc").lastIndexOf(CSTR("ab")));
	EXPECT_EQ(6, CSTR("abcabcabc").lastIndexOf(CSTR("abc")));
	EXPECT_EQ(-1, CSTR("abcabc").lastIndexOf(CSTR("abd")));
	EXPECT_EQ(2, CSTR("ababcab").lastIndexOf(CSTR("abc")));
	EXPECT_EQ(2, CSTR("ABABAC").lastIndexOf(CSTR("ABAC")));
}

}
