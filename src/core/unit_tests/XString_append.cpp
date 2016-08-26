
#include "gtest/gtest.h"
#include "fianet-core.h"

using namespace Fianet;

namespace {

TEST (XStringTest, append_works)
{
	XString s("aaa"), s2("bbb");

	// L'ajout de "" est sans effet (chaine vide)
	EXPECT_EQ ("aaa", s.append(""));
	EXPECT_EQ ((size_t)3, s.length());

	// Mais l'ajout de "\0" a bien l'effet escompté
	EXPECT_EQ (CSTR("aaa" "\0"), s.append(String("", 1)));
	EXPECT_EQ ((size_t)4, s.length());

	EXPECT_EQ ("bbb ccc", s2.append(" ccc", 4));
	EXPECT_EQ ("bbb ccc cc", s2.append(" ccc", 3));

	EXPECT_EQ (CSTR("aaa" "\0" "bbb ccc cc"), s.append(s2));
}


TEST (XStringTest, appendInt_works)
{
	XString s;

	EXPECT_EQ (UINT32_MAX, s.appendUint32(UINT32_MAX).toUint32());

	s.clear();
	EXPECT_EQ (INT32_MAX, s.appendInt32(INT32_MAX).toInt32());

	s.clear();
	EXPECT_EQ (INT64_MAX, s.appendInt64(INT64_MAX).toInt64());

	s.clear();
	EXPECT_EQ (UINT64_MAX, s.appendUint64(UINT64_MAX).toUint64());
}

} // namespace
