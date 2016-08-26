
#include "gtest/gtest.h"
#include "fianet-core.h"

using namespace Fianet;

namespace {

TEST (XStringTest, XString_resize_works)
{
	XString s("truc");
	const char* ptr = s.cstr();
	size_t capa = s.capacity();

	EXPECT_EQ (4, s.length());
	EXPECT_EQ (ptr, s.cstr());

	EXPECT_THROW (s.resize(s.capacity()+256), Exception);

	EXPECT_EQ (4, s.length());
	EXPECT_EQ (ptr, s.cstr());

	memset (const_cast<char*>(ptr+4), '@', capa-4);

	s.resize(8);
	// Normalement l'ajustement n'a rien modifi�.
	EXPECT_EQ (capa, s.capacity());
	EXPECT_EQ (8, s.length());
	EXPECT_EQ (ptr, s.cstr());

	// L'ajustement a concat�n� le NIL terminal. On a donc "truc@@@@\0"
	// dans le buffer, qu'on peut comparer avec une cha�ne C classique.
	EXPECT_STREQ("truc@@@@", s.cstr());


	// On peut ajuster la taille tant qu'on ne r�alloue pas.
	EXPECT_NO_THROW (s.resize(s.capacity()-1));

	// L'ajustement ne doit pas avoir modifi� le pointeur et la capacit�
	// de l'objet.
	EXPECT_EQ (capa, s.capacity());
	EXPECT_EQ (ptr, s.cstr());
 
	// On provoque une allocation qui change les donn�es internes.
	s.reserve (1024);
	EXPECT_GT (s.capacity(), capa);
	EXPECT_NE (s.cstr(), ptr);
	EXPECT_EQ (capa-1, s.length());

	// On peut jouer sur les 1024 premiers octets.
	ptr = s.cstr();
	capa = s.capacity();

	memset (const_cast<char*>(ptr+8), '#', 1024-8);

	s.resize(12);
	EXPECT_EQ (capa, s.capacity());
	EXPECT_EQ (12, s.length());
	EXPECT_EQ (ptr, s.cstr());

	EXPECT_STREQ("truc@@@@####", s.cstr());
}

} // namespace