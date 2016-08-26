/*
 * FIA-NET C++ COMMONS
 *
 * A library of core components developped for Fia-Net products.
 * Copyright 2008 - 2016 FIA-NET S.A.
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "gtest/gtest.h"
#include "fianet-core.h"

#include "StringTokenizer.h"

using namespace Fianet;

namespace {

TEST (StringTokenizerTest, StringTokenizer_empty)
{
	StringTokenizer tk("");
	StringTokenizer::Iterator it = tk.begin(' ');

	EXPECT_EQ (tk.end(), it);

	// Once end() is reached, ++ does nothing.
	EXPECT_EQ (tk.end(), ++it);
	EXPECT_EQ (tk.end(), it);

	/* TESTS ReverseIterator */
	StringTokenizer::ReverseIterator rit = tk.rbegin(' ');

	EXPECT_EQ (tk.rend(), rit);

	// Once rend() is reached, ++ does nothing.
	EXPECT_EQ (tk.rend(), ++rit);
	EXPECT_EQ (tk.rend(), rit);
}

TEST (StringTokenizerTest, StringTokenizer_notfound)
{
	StringTokenizer tk("blabla");
	StringTokenizer::Iterator it = tk.begin('x');

	EXPECT_EQ (CSTR("blabla"), *it++);
	EXPECT_EQ (tk.end(), it);

	// TESTS ReverseIterator
	StringTokenizer::ReverseIterator rit = tk.rbegin('x');

	EXPECT_EQ (CSTR("blabla"), *rit++);
	EXPECT_EQ (tk.rend(), rit);
}

TEST (StringTokenizerTest, StringTokenizer_common)
{
	StringTokenizer tk("ceci est une chaine");
	StringTokenizer::Iterator it = tk.begin(' ');

	EXPECT_EQ (0, it.index());
	EXPECT_EQ (CSTR("ceci"), *it++);

	EXPECT_EQ (1, it.index());
	EXPECT_EQ (CSTR("est"), *it++);

	EXPECT_EQ (2, it.index());
	EXPECT_EQ (CSTR("une"), *it++);

	EXPECT_EQ (3, it.index());
	EXPECT_EQ (CSTR("chaine"), *it++);
	
	EXPECT_EQ (-1, it.index());
	EXPECT_EQ (tk.end(), it);

	// TESTS ReverseIterator
	StringTokenizer::ReverseIterator rit = tk.rbegin(' ');

	EXPECT_EQ (0, rit.index());
	EXPECT_EQ (CSTR("chaine"), *rit++);

	EXPECT_EQ (1, rit.index());
	EXPECT_EQ (CSTR("une"), *rit++);

	EXPECT_EQ (2, rit.index());
	EXPECT_EQ (CSTR("est"), *rit++);

	EXPECT_EQ (3, rit.index());
	EXPECT_EQ (CSTR("ceci"), *rit++);

	EXPECT_EQ (-1, rit.index());
	EXPECT_EQ (tk.rend(), rit);
}

TEST (StringTokenizerTest, StringTokenizer_common_withLongDelimiter)
{
	StringTokenizer tk("ceci/-/est//une/-/chaine/-/avec un /-/ long delimiteur");
	StringTokenizer::Iterator it = tk.begin("/-/");

	EXPECT_EQ (0, it.index());
	EXPECT_EQ (CSTR("ceci"), *it++);

	EXPECT_EQ (1, it.index());
	EXPECT_EQ (CSTR("est//une"), *it++);

	EXPECT_EQ (2, it.index());
	EXPECT_EQ (CSTR("chaine"), *it++);

	EXPECT_EQ (3, it.index());
	EXPECT_EQ (CSTR("avec un "), *it++);

	EXPECT_EQ (4, it.index());
	EXPECT_EQ (CSTR(" long delimiteur"), *it++);

	EXPECT_EQ (-1, it.index());
	EXPECT_EQ (tk.end(), it);

	// TESTS ReverseIterator
	StringTokenizer::ReverseIterator rit = tk.rbegin("/-/");

	EXPECT_EQ (0, rit.index());
	EXPECT_EQ (CSTR(" long delimiteur"), *rit++);

	EXPECT_EQ (1, rit.index());
	EXPECT_EQ (CSTR("avec un "), *rit++);

	EXPECT_EQ (2, rit.index());
	EXPECT_EQ (CSTR("chaine"), *rit++);

	EXPECT_EQ (3, rit.index());
	EXPECT_EQ (CSTR("est//une"), *rit++);

	EXPECT_EQ (4, rit.index());
	EXPECT_EQ (CSTR("ceci"), *rit++);

	EXPECT_EQ (-1, rit.index());
	EXPECT_EQ (tk.rend(), rit);
}

TEST (StringTokenizerTest, StringTokenizer_successive_delimiter)
{
	StringTokenizer tk("|champ1||champ2||champ3|");
	StringTokenizer::Iterator it = tk.begin('|');

	EXPECT_EQ (0, it.index());
	EXPECT_EQ (CSTR(""), *it++);

	EXPECT_EQ (1, it.index());
	EXPECT_EQ (CSTR("champ1"), *it++);

	EXPECT_EQ (2, it.index());
	EXPECT_EQ (CSTR(""), *it++);

	EXPECT_EQ (3, it.index());
	EXPECT_EQ (CSTR("champ2"), *it++);

	EXPECT_EQ (4, it.index());
	EXPECT_EQ (CSTR(""), *it++);
	
	EXPECT_EQ (5, it.index());
	EXPECT_EQ (CSTR("champ3"), *it++);
	
	EXPECT_EQ (6, it.index());
	EXPECT_EQ (CSTR(""), *it++);
	
	EXPECT_EQ (-1, it.index());
	EXPECT_EQ (tk.end(), it);

	// TESTS ReverseIterator
	StringTokenizer::ReverseIterator rit = tk.rbegin('|');

	EXPECT_EQ (0, rit.index());
	EXPECT_EQ (CSTR(""), *rit++);

	EXPECT_EQ (1, rit.index());
	EXPECT_EQ (CSTR("champ3"), *rit++);

	EXPECT_EQ (2, rit.index());
	EXPECT_EQ (CSTR(""), *rit++);

	EXPECT_EQ (3, rit.index());
	EXPECT_EQ (CSTR("champ2"), *rit++);

	EXPECT_EQ (4, rit.index());
	EXPECT_EQ (CSTR(""), *rit++);

	EXPECT_EQ (5, rit.index());
	EXPECT_EQ (CSTR("champ1"), *rit++);

	EXPECT_EQ (6, rit.index());
	EXPECT_EQ (CSTR(""), *rit++);
	
	EXPECT_EQ (-1, rit.index());
	EXPECT_EQ (tk.rend(), rit);
}

TEST (StringTokenizerTest, StringTokenizer_successive_LongDelimiter)
{
	// that's not Morse code
	StringTokenizer tk("-..--..---..----..--.-..--..-..-");

	StringTokenizer::Iterator it = tk.begin("-..-");

	EXPECT_EQ (0, it.index());
	EXPECT_EQ (CSTR(""), *it++);

	EXPECT_EQ (1, it.index());
	EXPECT_EQ (CSTR(""), *it++);

	EXPECT_EQ (2, it.index());
	EXPECT_EQ (CSTR("-"), *it++);

	EXPECT_EQ (3, it.index());
	EXPECT_EQ (CSTR("--"), *it++);

	EXPECT_EQ (4, it.index());
	EXPECT_EQ (CSTR("-."), *it++);

	EXPECT_EQ (5, it.index());
	EXPECT_EQ (CSTR(""), *it++);

	EXPECT_EQ (6, it.index());
	EXPECT_EQ (CSTR("..-"), *it++);

	// TESTS ReverseIterator slightly different results
	StringTokenizer::ReverseIterator rit = tk.rbegin("-..-");

	EXPECT_EQ (0, rit.index());
	EXPECT_EQ (CSTR(""), *rit++);

	EXPECT_EQ (1, rit.index());
	EXPECT_EQ (CSTR("-.."), *rit++);

	EXPECT_EQ (2, rit.index());
	EXPECT_EQ (CSTR("-."), *rit++);

	EXPECT_EQ (3, rit.index());
	EXPECT_EQ (CSTR("--"), *rit++);

	EXPECT_EQ (4, rit.index());
	EXPECT_EQ (CSTR("-"), *rit++);

	EXPECT_EQ (5, rit.index());
	EXPECT_EQ (CSTR(""), *rit++);

	EXPECT_EQ (6, rit.index());
	EXPECT_EQ (CSTR(""), *rit++);

}

}
