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
#ifndef FIANET_STRINGTOKENIZER_H
#define	FIANET_STRINGTOKENIZER_H

#include "fianet-core.h"

namespace Fianet {

/**
 * @class StringTokenizer
 * As its name suggests, this class is a string tokenizer. It is useful for
 * getting slices of strings using separators. Provides an Iterator class for
 * left-to-right operations, and a ReverseIterator for right-to-left.
 *
 * As the tokenizer manipulates String instances, the String data cannot
 * be modified.
 *
 */
class StringTokenizer {
public:
	class Iterator;
	class ReverseIterator;

protected:
	const String& myString;

private:
	StringTokenizer();
	StringTokenizer& operator = (const StringTokenizer&);
	StringTokenizer(const StringTokenizer&);

public:
	~StringTokenizer()
	{ }

	/**
	 * Creates a tokenizer instance on a target string.
	 * The string *must* exist until the destruction of
	 * the iterator.
     * @param str
     */
	StringTokenizer (const String& str);

	/// @return the string targeted by the tokenizer.
	const String& str() const {
		return myString;
	}

	/**
	 * Creates an iterator based on a char delimiter.
	 * @param delimiter the delimiter to use for separating tokens.
	 * @return the Iterator containing the first token
	 * found in the string, StringTokenizer::end()
	 * if no token is found in the string.
	 */
	Iterator begin (char delimiter);

	/**
	 * Creates an iterator based on a String delimiter.
	 * @param delimiter the delimiter to use for separating tokens.
	 * @return the Iterator containing the first token
	 * found in the string, StringTokenizer::end()
	 * if no token is found in the string.
	 */
	Iterator begin (const String& delimiter);

	/**
	 * 'No more token' mark.
     * @return an empty Iterator.
     */
	static Iterator& end();

	/**
	 * Creates a reverse iterator based on a char delimiter.
	 * @param delimiter the delimiter to use for separating tokens.
	 * @return the ReverseIterator containing the first token
	 * found in the end of the string, StringTokenizer::rend()
	 * if no token is found in the string.
	 */
	ReverseIterator rbegin (char delimiter);

	/**
	 * Creates a reverse iterator based on a String delimiter.
	 * @param delimiter the delimiter to use for separating tokens.
	 * @return the ReverseIterator containing the first token
	 * found in the end of the string, StringTokenizer::rend()
	 * if no token is found in the string.
	 */
	ReverseIterator rbegin (const String& delimiter);

	/**
	 * 'No more token' mark for reverse iterator.
     * @return an empty ReverseIterator.
     */
	static ReverseIterator& rend();
};

/**
 * @class StringTokenizer::Iterator
 * Allows to walk through all the tokens extracted by a StringTokenizer,
 * from left to right.
 * 
 * @note The StringTokenizer instance must exist while all the corresponding
 * Iterators are in use.
 *
 */
class StringTokenizer::Iterator {
	friend Iterator StringTokenizer::begin(char delimiter);
	friend Iterator StringTokenizer::begin(const String& delimiter);

	StringTokenizer* owner;

	XString delimiter;
	int delimpos;

	uint32_t rank;
	String token;

	Iterator (StringTokenizer* owner, const String& delimiter);

public:
	Iterator()
	: owner(0), delimiter(), delimpos(-1), rank(-1)	, token() {

	}
	Iterator (const Iterator& it)
	: owner(it.owner), delimiter(it.delimiter), delimpos(it.delimpos), rank(it.rank), token(it.token) {
	}

	/// @return the rank of the token in the string.
	int32_t index() {
		return rank;
	}

	/// @return the token pointer by the iterator.
	const String& value() const {
		return token;
	}

	/// Assigns to *this
	Iterator& operator = (const Iterator& it) {
		if (this != &it) {
			this->owner = it.owner;
			this->delimiter = it.delimiter;
			this->delimpos = it.delimpos;
			this->rank = it.rank;
			this->token.adopt(it.token);
		}
		return *this;
	}

	/// @see value()
	const String& operator*() const {
		return token;
	}

	/// @see value()
	const String& operator->() const {
		return token;
	}

	/// @return true if *this is equivalent to iter
	bool operator == (const Iterator& iter) const {
		return (this == &iter || (owner == iter.owner && delimiter == iter.delimiter && delimpos == iter.delimpos && rank == iter.rank && token == iter.token));
	}
	/// @return true if *this is not equivalent to iter
	bool operator != (const Iterator& iter) const {
		return !this->operator == (iter);
	}

	// prefix increment
	Iterator& operator ++();

	// postfix increment
	Iterator operator ++ (UNUSED_PARAM(int dummy)) {
		Iterator bak(*this);
		this->operator++();
		return bak;
	}
};

/**
 * @class StringTokenizer::ReverseIterator
 * Allows to walk through all the tokens extracted by a StringTokenizer,
 * from right to left.
 *
 * @note The StringTokenizer instance must exist while all the corresponding
 * Iterators are in use.
 *
 */
class StringTokenizer::ReverseIterator {
	friend ReverseIterator StringTokenizer::rbegin(char delimiter);
	friend ReverseIterator StringTokenizer::rbegin(const String& delimiter);

	StringTokenizer* owner;

	XString delimiter;
	int delimpos;

	uint32_t rank;
	String token;

	ReverseIterator (StringTokenizer* owner, const String& delimiter);

public:
	ReverseIterator()
	: owner(0), delimiter(), delimpos(-1), rank(-1)	, token() 
	{ }
	ReverseIterator (const ReverseIterator& it)
	: owner(it.owner), delimiter(it.delimiter), delimpos(it.delimpos), rank(it.rank), token(it.token) 
	{ }

	/// @return the rank of the token in the string.
	int32_t index() {
		return rank;
	}

	/// @return the token pointer by the iterator.
	const String& value() const {
		return token;
	}

	/// Assigns to *this
	ReverseIterator& operator = (const ReverseIterator& it) {
		if (this != &it) {
			this->owner = it.owner;
			this->delimiter = it.delimiter;
			this->delimpos = it.delimpos;
			this->rank = it.rank;
			this->token.adopt(it.token);
		}
		return *this;
	}

	/// @see value()
	const String& operator*() const {
		return token;
	}

	/// @see value()
	const String& operator->() const {
		return token;
	}

	/// @return true if *this is equivalent to iter
	bool operator == (const ReverseIterator& iter) const {
		return (this == &iter || (owner == iter.owner && delimiter == iter.delimiter && delimpos == iter.delimpos && rank == iter.rank && token == iter.token));
	}

	/// @return true if *this is not equivalent to iter
	bool operator != (const ReverseIterator& iter) const {
		return !this->operator == (iter);
	}

	// prefix increment
	ReverseIterator& operator ++();

	// postfix increment
	ReverseIterator operator ++ (UNUSED_PARAM(int dummy)) {
		ReverseIterator bak(*this);
		this->operator++();
		return bak;
	}
};



} // namespace Fianet

#endif	/* FIANET_STRINGTOKENIZER_H */
