
#include "gtest/gtest.h"
#include "fianet-core.h"

using namespace Fianet;

TEST (StringTest, compareTo_works)
{
	String s("aaa");

	EXPECT_EQ (0, s.compareTo(s));

	EXPECT_EQ (0, CSTR("").compareTo(""));
	EXPECT_EQ (0, CSTR("abc").compareTo("abc"));

	EXPECT_GT (0, CSTR("").compareTo("abc"));
	EXPECT_GT (0, CSTR("Abc").compareTo("abc"));
	EXPECT_GT (0, CSTR("Def").compareTo("abc"));
	EXPECT_GT (0, CSTR("abc").compareTo("abcd"));
	EXPECT_GT (0, CSTR("abc").compareTo("def"));

	EXPECT_LT (0, CSTR("def").compareTo("abc"));
	EXPECT_LT (0, CSTR("def").compareTo(""));
	EXPECT_LT (0, CSTR("abcd").compareTo("abc"));

	// Tests sur des chaines binaires
	EXPECT_EQ (0, CSTR("abc" "\0" "defgh").icompareTo(CSTR("abc" "\0" "defgh")));
	EXPECT_LT (0, CSTR("abc" "\0" "defgh").icompareTo(CSTR("abc" "\0")));
	EXPECT_LT (0, CSTR("\0" "abc" "\0" "defgh").icompareTo(CSTR("\0" "abc" "\0")));
}

TEST (StringTest, icompareTo_works)
{
	String s("aaa");

	EXPECT_EQ (s.icompareTo(s), 0);

	EXPECT_EQ (0, CSTR("").icompareTo(""));
	EXPECT_EQ (0, CSTR("abc").icompareTo("abc"));

	EXPECT_GT (0, CSTR("").icompareTo("abc"));
	EXPECT_EQ (0, CSTR("Abc").icompareTo("abc"));
	EXPECT_GT (0, CSTR("abc").icompareTo("abcd"));
	EXPECT_GT (0, CSTR("abc").icompareTo("def"));

	EXPECT_LT (0, CSTR("def").icompareTo(""));
	EXPECT_LT (0, CSTR("def").icompareTo("abc"));
	EXPECT_LT (0, CSTR("Def").icompareTo("abc"));
	EXPECT_LT (0, CSTR("Def").icompareTo("Abc"));
	EXPECT_LT (0, CSTR("abcd").icompareTo("abc"));

	EXPECT_EQ (0, CSTR("abcdefgh").icompareTo("AbCdEfGh"));

	// Tests sur des chaines binaires
	EXPECT_EQ (0, CSTR("abc" "\0" "defgh").icompareTo(CSTR("AbC" "\0" "dEfGh")));
	EXPECT_LT (0, CSTR("abc" "\0" "defgh").icompareTo(CSTR("AbC" "\0")));
	EXPECT_LT (0, CSTR("\0" "abc" "\0" "defgh").icompareTo(CSTR("\0" "AbC" "\0")));
}


TEST (StringTest, contains_works)
{
	String s("aaa");

	EXPECT_TRUE (s.contains(""));
	EXPECT_TRUE (s.contains("a"));
	EXPECT_TRUE (s.contains("aaa"));
	EXPECT_FALSE (s.contains("aaaa"));
	EXPECT_FALSE (s.contains("b"));

	// Tests sur les chaînes contenant du binaire.
	// On utiliser CSTR pour éviter l'appel à strlen()
	// dans le constructeur String::String (const char*)
	String s2("a" "\0" "a", 3);

	EXPECT_TRUE (s2.contains(CSTR("\0")));
	EXPECT_TRUE (s2.contains(CSTR("a")));
	EXPECT_TRUE (s2.contains(CSTR("a" "\0" "a")));

}

TEST (StringTest, icontains_works)
{
	String s("aaa");

	EXPECT_TRUE (s.icontains(""));
	EXPECT_TRUE (s.icontains("a"));
	EXPECT_TRUE (s.icontains("aaa"));
	EXPECT_FALSE (s.icontains("aaaa"));
	EXPECT_FALSE (s.icontains("b"));

	EXPECT_TRUE (s.icontains("A"));
	EXPECT_TRUE (s.icontains("aAa"));
	EXPECT_TRUE (s.icontains("aaA"));
	EXPECT_TRUE (s.icontains("AAA"));
	EXPECT_FALSE (s.icontains("B"));

	// Tests sur les chaînes contenant du binaire.
	// On utiliser CSTR pour éviter l'appel à strlen()
	// dans le constructeur String::String (const char*)
	String s2("a" "\0" "a", 3);

	EXPECT_TRUE (s2.icontains(CSTR("\0")));
	EXPECT_TRUE (s2.icontains(CSTR("a")));
	EXPECT_TRUE (s2.icontains(CSTR("A")));
	EXPECT_TRUE (s2.icontains(CSTR("a" "\0" "a")));
	EXPECT_TRUE (s2.icontains(CSTR("a" "\0" "A")));
}


TEST (StringTest, startsWith_works)
{
	String s("the quick brown fox jumps over the" "\0" "lazy dog", 43);

	// <true> est renvoyé avec une chaîne vide.
	EXPECT_TRUE (s.startsWith(""));

	EXPECT_TRUE (CSTR("").startsWith(""));

	EXPECT_TRUE (s.startsWith(s));
	EXPECT_TRUE (s.startsWith("the"));
	EXPECT_TRUE (s.startsWith(CSTR("the quick brown fox jumps over the" "\0" "lazy dog")));
	EXPECT_FALSE (s.startsWith("lazy dog"));
}


TEST (StringTest, istartsWith_works)
{
	String s("the quick brown fox jumps over the" "\0" "lazy dog", 43);

	// <true> est renvoyé avec une chaîne vide.
	EXPECT_TRUE (s.istartsWith(""));

	EXPECT_TRUE (CSTR("").istartsWith(""));

	EXPECT_TRUE (s.istartsWith(s));
	EXPECT_TRUE (s.istartsWith("the"));
	EXPECT_TRUE (s.istartsWith(CSTR("the quick brown fox jumps over the" "\0" "lazy dog")));
	EXPECT_FALSE (s.istartsWith("lazy dog"));

	EXPECT_TRUE (s.istartsWith("thE"));
	EXPECT_TRUE (s.istartsWith(CSTR("tHe quick Brown fox jumps over the" "\0" "lazy dog")));
	EXPECT_FALSE (s.istartsWith("lazy dOg"));
}


TEST (StringTest, endsWith_works)
{
	String s("the quick brown fox jumps over the" "\0" "lazy dog", 43);

	// <true> est renvoyé avec une chaîne vide.
	EXPECT_TRUE (s.endsWith(""));

	EXPECT_TRUE (CSTR("").endsWith(""));

	EXPECT_TRUE (s.endsWith(s));
	EXPECT_FALSE (s.endsWith("the"));
	EXPECT_TRUE (s.endsWith("dog"));
	EXPECT_TRUE (s.endsWith(CSTR("the quick brown fox jumps over the" "\0" "lazy dog")));
	EXPECT_TRUE (s.endsWith("lazy dog"));
}


TEST (StringTest, indexOf_works)
{
	String s("the quick brown fox jumps over the" "\0" "lazy dog", 43);

	EXPECT_EQ (s.indexOf ("the quick blue fox"), -1);

	EXPECT_EQ (s.indexOf(s), 0);
	EXPECT_EQ (s.indexOf("the"), 0);
	EXPECT_EQ (s.indexOf(CSTR("the" "\0")), 31);
	EXPECT_EQ (s.indexOf(CSTR("\0")), 34);

	// Vérifier que le "\0" terminal n'est pas pris en compte dans s
	// On ne doit donc pas trouver "dog\0" dans s.
	EXPECT_EQ (s.indexOf(CSTR("g" "\0")), -1);

	// Version 1 argument char
	EXPECT_EQ (s.indexOfChar ('\0'), 34);
	EXPECT_EQ (s.indexOfChar ('h'), 1);
	EXPECT_EQ (s.indexOfChar ('-'), -1);
}

TEST (StringTest, lastIndexOf_works)
{
	String s("the quick brown fox jumps over the" "\0" "lazy dog", 43);

	EXPECT_EQ (s.lastIndexOf ("the quick blue fox"), -1);

	EXPECT_EQ (s.lastIndexOf(s), 0);
	EXPECT_EQ (s.lastIndexOf("fox"), 16);
	EXPECT_EQ (s.lastIndexOf("the"), 31);
	EXPECT_EQ (s.lastIndexOf(CSTR("the" "\0")), 31);
	EXPECT_EQ (s.lastIndexOf(CSTR("\0")), 34);

	// Vérifier que le "\0" terminal n'est pas pris en compte :
	// On ne doit donc pas trouver "dog\0" dans s.
	EXPECT_EQ (s.lastIndexOf(CSTR("dog" "\0")), -1);

	// Version 1 argument char
	EXPECT_EQ (s.lastIndexOfChar ('\0'), 34);
	EXPECT_EQ (s.lastIndexOfChar ('d'), 40);
	EXPECT_EQ (s.lastIndexOfChar ('-'), -1);
}
