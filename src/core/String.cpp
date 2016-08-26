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
#include "fianet-core.h"
#include "String.h"
#include <cctype>
#include <cstdlib>
#include <errno.h>
#include <stdint.h>
#include <limits.h>

// Adjust some function names depending on the bit size of the platform.
#if (__WORDSIZE == 64)
	#define strtoint	strtol
	#define isIntOutOfRange(v) (v > INT_MAX || v < INT_MIN)

	#define strtoint32	strtol
	#define isInt32OutOfRange(v) (v > INT32_MAX || v < INT32_MIN)

	#define strtouint32	strtoul
	#define isUint32OutOfRange(v) (v > UINT32_MAX)

	#define strtoint64	strtol
	#define isInt64OutOfRange(v) (errno == ERANGE && (v == INT64_MAX || v == INT64_MIN))

	#define strtouint64	strtoul
	#define isUint64OutOfRange(v) (errno == ERANGE && (v == UINT64_MAX))
#else
	#define strtoint	strtol
	#define isIntOutOfRange(v) (errno == ERANGE && (v == INT_MAX || v == INT_MIN))

	#define strtoint32	strtol
	#define isInt32OutOfRange(v) (errno == ERANGE && (v == INT32_MAX || v == INT32_MIN))

	#define strtouint32	strtoul
	#define isUint32OutOfRange(v) (errno == ERANGE && (v == UINT32_MAX))

	#define strtoint64	strtoll
	#define isInt64OutOfRange(v) (errno == ERANGE && (v == INT64_MAX || v == INT64_MIN))

	#define strtouint64	strtoull
	#define isUint64OutOfRange(v) (errno == ERANGE && (v == UINT64_MAX))
#endif

namespace Fianet {

static const char* blank_str = "";

// Look for s2 in s1
uint8_t* memfind (const void* s1, size_t len_s1, const void* s2, size_t len_s2)
{
	const uint8_t* ptr1 = static_cast<const uint8_t*>(s1);
	const uint8_t* ptr2 = static_cast<const uint8_t*>(s2);
	const uint8_t* end = ptr1 + len_s1;
	ssize_t ln = len_s1;

	while (ln > 0) {
		ptr1 = (uint8_t*) memchr(ptr1, (int)*ptr2, ln);
		if (!ptr1 || (end - ptr1) < static_cast<ssize_t>(len_s2))
			break;  // Not found

		if (memcmp(ptr1, ptr2, len_s2) == 0)
			return const_cast<uint8_t*>(ptr1);

		++ptr1;
		ln = end - ptr1;
	}

	return 0;
}
// same but case-insensitive
uint8_t* memifind (const void* s1, size_t len_s1, const void* s2, size_t len_s2)
{
	const uint8_t* ptr1 = static_cast<const uint8_t*>(s1);
	const uint8_t* ptr2 = static_cast<const uint8_t*>(s2);
	ssize_t ln = len_s1;

	while (ln > 0) {
		if (toupper(static_cast<int>(*ptr1)) == toupper(static_cast<int>(*ptr2))) {
			if (ln < static_cast<ssize_t>(len_s2))
				break;

			size_t nb = 1;
			for (; nb < len_s2; nb++) {
				if (toupper(static_cast<int>(*(ptr1+nb))) != toupper(static_cast<int>(*(ptr2+nb))))
					break;
			}

			if (nb == len_s2) {
				return const_cast<uint8_t*>(ptr1);
			}
		}
		++ptr1;
		ln--;
	}

	return 0;
}

//
int memicompare (const void* s1, const void* s2, size_t sz)
{
	const uint8_t* ptr1 = static_cast<const uint8_t*>(s1);
	const uint8_t* ptr2 = static_cast<const uint8_t*>(s2);
	const uint8_t* end = ptr1 + sz;
	int res = 0;

	while (ptr1 < end) {
		res = (toupper(static_cast<int>(*ptr1)) - toupper(static_cast<int>(*ptr2)));
		if (res != 0) {
			return res;
		}
		++ptr1;
		++ptr2;
	}

	return 0;
}

String::~String()
{
}

String::String()
	: ptr((uint8_t*)blank_str), len(0)
{
}

String::String (const char* addr, size_t ln)
	: ptr((uint8_t*)addr), len(ln)
{
}

String::String (const String& s)
	: ptr(s.ptr), len(s.len)
{
}

const String& String::blank()
{
	static String blank;
	return blank;
}

const String& String::CRLF()
{
	static String crlf("\x0d\x0a", 2);
	return crlf;
}

String& String::adopt (const char* addr, size_t ln)
{
	ptr = (uint8_t*)addr;
	len = ln;
	return *this;
}

String& String::adopt (const String& src)
{
	if (&src != this) {
		ptr = src.ptr;
		len = src.len;
	}

	return *this;
}

bool String::equals (const String& s) const
{
	return ((&s == this) || (s.ptr == this->ptr) || (s.length() == length() && (length() == 0 || (std::memcmp (ptr, s.ptr, length()) == 0))));
}

bool String::iequals (const String& s) const
{
	return ((&s == this) || (s.ptr == this->ptr) || (s.length() == length() && (length() == 0 || (memicompare (cstr(), s.cstr(), length()) == 0))));
}

bool String::contains (const String& s) const
{
	return ((&s == this) || (s.ptr == this->ptr) || (length() > 0 && length() >= s.length() && (s.length() == 0 || memfind (bytes(), length(), s.ptr, s.length()) != 0)));
}

bool String::icontains (const String& s) const
{
	return ((&s == this) || (s.ptr == this->ptr) || (length() > 0 && length() >= s.length() && (s.length() == 0 || memifind (bytes(), length(), s.bytes(), s.length()) != 0)));
}

bool String::startsWith (const String& s) const
{
	return ( (&s == this) || (s.ptr == this->ptr) || (length() >= s.length() && (s.length() == 0 || std::memcmp (ptr, s.ptr, s.length()) == 0)) );
}

bool String::istartsWith (const String& s) const
{
	return ( (&s == this) || (s.ptr == this->ptr) || (length() >= s.length() && (s.length() == 0 || memicompare (bytes(), s.bytes(), s.length()) == 0)) );
}

bool String::endsWith (const String& s) const
{
	return ((&s == this) || (s.ptr == this->ptr) || (length() >= s.length() && (s.length() == 0 || std::memcmp (bytes()+length()-s.length(), s.bytes(), s.length()) == 0)) );
}

bool String::iendsWith (const String& s) const
{
	return ( (&s == this) || (s.ptr == this->ptr) || (s.length() <= length() && (s.length() == 0 || memicompare (bytes()+length()-s.length(), s.bytes(), s.length()) == 0)) );
}

int String::compareTo (const String& s) const
{
	if (&s == this || s.ptr == this->ptr) {
		return 0;
	}

	int res;

	if (length() < s.length()) {
		res = ::memcmp (cstr(), s.cstr(), length());
		if (res == 0) {
			return -1;
		}
	} else if (length() > s.length()) {
		res = ::memcmp (cstr(), s.cstr(), s.length());
		if (res == 0) {
			return 1;
		}
	} else {
		res = ::memcmp (cstr(), s.cstr(), length());
	}
	return res;
}

int String::compareTo (const String& s, uint32_t nbChars) const
{
	if (&s == this || s.ptr == this->ptr) {
		return 0;
	}

	uint32_t lenMax = (length() < s.length()) ? length() : s.length();

	if (nbChars > lenMax) {
		nbChars = lenMax;
	}

	return ::memcmp (cstr(), (const char*)s.cstr(), nbChars);
}


int String::icompareTo (const String& s) const
{
	if (&s == this || s.ptr == this->ptr) {
		return 0;
	}

	int res;

	if (length() < s.length()) {
		res = memicompare (cstr(), s.cstr(), length());
		if (res == 0) {
			return -1;
		}
	} else if (length() > s.length()) {
		res = memicompare (cstr(), s.cstr(), s.length());
		if (res == 0) {
			return 1;
		}
	} else {
		res = memicompare (cstr(), s.cstr(), length());
	}
	return res;
}



int String::icompareTo (const String& s, uint32_t nbChars) const
{
	if (&s == this || s.ptr == this->ptr) {
		return 0;
	}

	uint32_t lenMax = (length() < s.length()) ? length() : s.length();

	if (nbChars > lenMax) {
		nbChars = lenMax;
	}

	return (memicompare (cstr(), s.cstr(), nbChars));
}

ssize_t String::indexOfChar (char c) const
{
	const uint8_t* p = (uint8_t*) memchr (ptr, (int)c, len);
	return (ssize_t) ((p) ? (p - ptr) : -1);
}

ssize_t String::indexOf (const String& s) const
{
	if (s.length() == 0) {
		return -1;
	}

	const uint8_t* p = (uint8_t*) memfind (ptr, len, s.ptr, s.len);
	return (ssize_t) ((p) ? (p - ptr) : -1);
}

ssize_t String::lastIndexOfChar (char c) const
{
	register const uint8_t* p = ptr + len - 1;

	while (p >= ptr && *p != (uint8_t)c) {
		--p;
	}

	return (p >= ptr && *p == (uint8_t)c) ? (p - ptr) : -1;
}

ssize_t String::lastIndexOf (const String& s) const
{
	if (s.length() > 0 && length() >= s.length()) {
		char first = s.charAt(0);
		register const uint8_t* p = ptr + len - s.length();
		register const uint8_t* end = ptr + length();

		while (p >= ptr) {

			if (*p == first) {
				if ( (end-p) >= static_cast<int32_t>(s.length()) && !memcmp(p, s.cstr(), s.length()) ) {
					return (p-ptr);
				}
			}
			--p;
		}
	}

	return -1;
}

int32_t String::toInt() const
{
	if (length() == 0) {
		throw NumberFormatError();
	}
	char* endptr;
	char tmp[256];
	size_t lenmax = (sizeof(tmp) / sizeof(tmp[0])) - 1;

	if (length() < lenmax) {
		lenmax = length();
	}
	memcpy (tmp, ptr, lenmax);
	*(tmp+lenmax) = 0;

	errno = 0;
	long value = strtol (tmp, &endptr, 0);

	if (isInt32OutOfRange(value)) {
		throw NumberRangeError();
	} else if (errno == EINVAL || endptr == tmp || (size_t)(endptr-tmp) != length()) {
		throw NumberFormatError();
	}

	return static_cast<int>(value);
}

int32_t String::toInt32() const
{
	if (length() == 0) {
		throw NumberFormatError();
	}
	char* endptr;
	char tmp[256];
	size_t lenmax = (sizeof(tmp) / sizeof(tmp[0])) - 1;

	if (length() < lenmax) {
		lenmax = length();
	}
	memcpy (tmp, ptr, lenmax);
	*(tmp+lenmax) = 0;

	errno = 0;
	int32_t value = strtoint32 (tmp, &endptr, 0);

	if (isInt32OutOfRange(value)) {
		throw NumberRangeError();
	} else if (errno == EINVAL || endptr == tmp || (size_t)(endptr-tmp) != length()) {
		throw NumberFormatError();
	}

	return static_cast<int32_t>(value);
}

uint32_t String::toUint32() const
{
	if (length() == 0) {
		throw NumberFormatError();
	}
	char* endptr;
	char tmp[256];
	size_t lenmax = (sizeof(tmp) / sizeof(tmp[0])) - 1;

	if (length() < lenmax) {
		lenmax = length();
	}
	memcpy (tmp, ptr, lenmax);
	*(tmp+lenmax) = 0;

	errno = 0;
	uint32_t value = strtouint32 (tmp, &endptr, 0);

	if (isUint32OutOfRange(value)) {
		throw NumberRangeError();
	} else if (errno == EINVAL || endptr == tmp || (size_t)(endptr-tmp) != length()) {
		throw NumberFormatError();
	} else {
		// Contrairement � la libc, la conversion d'un nombre n�gatif d�clenche une erreur.
		if (indexOfChar('-') >= 0 && value != 0) {
			throw NumberRangeError();
		}
	}

	return static_cast<uint32_t>(value);
}

int64_t String::toInt64() const
{
	if (length() == 0) {
		throw NumberFormatError();
	}
	char* endptr;
	char tmp[256];
	size_t lenmax = (sizeof(tmp) / sizeof(tmp[0])) - 1;

	if (length() < lenmax) {
		lenmax = length();
	}
	memcpy (tmp, ptr, lenmax);
	*(tmp+lenmax) = 0;

	errno = 0;
	int64_t value = strtoint64 (tmp, &endptr, 0);

	if (isInt64OutOfRange(value)) {
		throw NumberRangeError();
	} else if (errno == EINVAL || endptr == tmp || (size_t)(endptr-tmp) != length()) {
		throw NumberFormatError();
	}

	return static_cast<int64_t>(value);
}

uint64_t String::toUint64() const
{
	if (length() == 0) {
		throw NumberFormatError();
	}
	char* endptr;
	char tmp[256];
	size_t lenmax = (sizeof(tmp) / sizeof(tmp[0])) - 1;

	if (length() < lenmax) {
		lenmax = length();
	}
	memcpy (tmp, ptr, lenmax);
	*(tmp+lenmax) = 0;

	errno = 0;
	uint64_t value = strtouint64 (tmp, &endptr, 0);

	if (isUint64OutOfRange(value)) {
		throw NumberRangeError();
	} else if (errno == EINVAL || endptr == tmp || (size_t)(endptr-tmp) != length()) {
		throw NumberFormatError();
	} else {
		// Contrairement � la libc, la conversion d'un nombre n�gatif d�clenche une erreur.
		if (indexOfChar('-') >= 0) {
			throw NumberRangeError();
		}
	}

	return static_cast<uint64_t>(value);
}

double String::toFloat() const
{
	if (length() == 0) {
		throw NumberFormatError();
	}
	char* endptr;
	char tmp[256];
	size_t lenmax = (sizeof(tmp) / sizeof(tmp[0])) - 1;

	if (length() < lenmax) {
		lenmax = length();
	}
	memcpy (tmp, ptr, lenmax);
	*(tmp+lenmax) = 0;

	errno = 0;
	double value = strtod (tmp, &endptr);

	if (endptr != tmp+length() || errno == EINVAL) {
		throw NumberFormatError();
	} else if (errno == ERANGE) {
		throw NumberRangeError("toFloat() conversion failed.");
	}

	return value;
}


String& String::ltrim()
{
	if (len) {
		const char* lptr = cstr();
		const char* endptr = cstr()+len-1;
		size_t newlen = len;

		while (lptr <= endptr && isspace ((int)*lptr)) {
			++lptr;
			--newlen;
		}

		if (newlen == 0) {
			len = 0;
		} else {
			adopt (lptr, newlen);
		}
	}
	return *this;
}

String& String::rtrim()
{
	if (len) {
		uint8_t* rptr = ptr+len-1;
		size_t newlen = len;

		while (rptr >= ptr && isspace ((int)*rptr)) {
			--rptr;
			--newlen;
		}

		len = newlen;
	}
	return *this;
}

String& String::trim()
{
	rtrim();
	return ltrim();
}

const String String::substr (int start, int nbchars) const
{
	// start n�gatif -> on compte � partir de la fin.
	if (start < 0) {
		start = length() + start;
	}

	// D�but de cha�ne en dehors de notre zone -> cha�ne vide.
	if (start < 0 || (start > static_cast<int>(length())) ) {
		return String::blank();
	}

	int available = length() - start;

	if (nbchars < 0) {
		nbchars = available + nbchars;
		if (nbchars < 0) {
			return String::blank();
		}
	} else {
		if (nbchars > available) {
			nbchars = available;
		}
	}

	return String (this->cstr()+start, nbchars);
}

const String String::substr (int start) const
{
	// start n�gatif -> on compte � partir de la fin.
	if (start < 0) {
		start = length() + start;
	}

	// D�but de cha�ne en dehors de notre zone -> cha�ne vide.
	if (start < 0 || (start > static_cast<int>(length()))) {
		return String::blank();
	}

	return String (this->cstr()+start, length()-start);
}


} // namespace Fianet

