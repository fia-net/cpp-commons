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
#include "StringTokenizer.h"

namespace Fianet {

StringTokenizer::StringTokenizer (const String& str)
: myString(str)
{

}


StringTokenizer::Iterator StringTokenizer::begin (const String& delimiter)
{
	return Iterator (this, delimiter);
}

StringTokenizer::Iterator StringTokenizer::begin(char delimiter)
{
	XString delim;
	delim.appendChar(delimiter);
	return Iterator (this, delim);
}

StringTokenizer::Iterator& StringTokenizer::end()
{
	static Iterator it;
	return it;
}


StringTokenizer::Iterator::Iterator(StringTokenizer* owner_, const String& delim)
 : owner(owner_), delimiter(delim), delimpos(0), rank(0), token()
{
	delimpos = owner->str().indexOf(delimiter);

	if (delimpos == -1) {
		token.adopt (owner->str());
		if (token.length() == 0) {
			*this = owner->end();
		}

	} else {
		token.adopt (owner->str().cstr(), delimpos);
	}
}

StringTokenizer::Iterator& StringTokenizer::Iterator::operator ++ ()
{
	if (delimpos == -1) {
		*this = StringTokenizer::end();

	} else {
		String sub (owner->str().substr (delimpos+delimiter.length()));

		int nextdp = sub.indexOf(delimiter);
		if (nextdp == -1) {
			token.adopt (sub);
			delimpos = -1;

		} else {
			token.adopt (sub.cstr(), nextdp);
			delimpos += nextdp+delimiter.length();
		}
		++rank;
	}

	return *this;
}


/**********************************************/
/* ReverseIterator */
/**********************************************/

StringTokenizer::ReverseIterator& StringTokenizer::rend()
{
	static ReverseIterator it;
	return it;
}


StringTokenizer::ReverseIterator StringTokenizer::rbegin(char delimiter)
{
	XString delim;

	delim.appendChar(delimiter);

	return ReverseIterator (this, delim);
}

StringTokenizer::ReverseIterator StringTokenizer::rbegin (const String& delimiter)
{
	return ReverseIterator (this, delimiter);
}

StringTokenizer::ReverseIterator::ReverseIterator(StringTokenizer* owner_, const String& delim)
 : owner(owner_), delimiter(delim), delimpos(0), rank(0), token()
{
	delimpos = owner->str().lastIndexOf(delimiter);

	if (delimpos == -1) {
		token.adopt (owner->str());
		if (token.length() == 0) {
			*this = owner->rend();
		}

	} else {
		token.adopt (owner->str().cstr() + delimpos + delimiter.length(), owner->str().length()-delimpos-delimiter.length());
	}
}

StringTokenizer::ReverseIterator& StringTokenizer::ReverseIterator::operator ++ ()
{
	if (delimpos == -1) {
		*this = StringTokenizer::rend();

	} else {
		String sub (owner->str().substr (0, delimpos));

		int nextdp = sub.lastIndexOf(delimiter);
		if (nextdp == -1) {
			token.adopt (sub);
			delimpos = -1;

		} else {
			token.adopt (sub.cstr()+nextdp+delimiter.length(), delimpos-nextdp-delimiter.length());
			delimpos = nextdp;
		}
		++rank;
	}

	return *this;
}



} // namespace Fianet
