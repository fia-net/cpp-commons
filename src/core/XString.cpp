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
#include "XString.h"
#include <stdarg.h>

namespace Fianet {

inline uint8_t* allocate (size_t sz)
{
	return (uint8_t*) std::malloc(sz);
}

inline uint8_t* realloc (uint8_t* ptr, size_t newsz)
{
	return(uint8_t*) std::realloc (ptr, newsz);
}

inline void release (uint8_t* addr)
{
	std::free (addr);
}

XString::~XString()
{
	if (ptr != buf) {
		release (ptr);
		ptr = 0;
	}
}

XString::XString()
	: String((const char*)buf, 0), capa(BUF_SIZE), growsize(DEFAULT_GROW_SIZE), buf()
{
	*buf = 0;
}

void XString::expand (size_t sz)
{
	size_t newsize = ((sz+capa) / growsize) * growsize;
	uint8_t* addr = 0;

	if (!newsize) {
		newsize = growsize;
	} else if ((sz+capa) % growsize) {
		newsize += growsize;
	}

	if (newsize > capa) {
		if (ptr == buf) {
			addr = allocate (newsize);
			if (!addr) {
				THROW ("XString::expand(): allocate() returned NULL");
			}
			memcpy (addr, buf, len);
			*(addr+len) = 0;

		} else {

			addr = realloc (ptr, newsize);
			if (!addr) {
				THROW ("XString::expand(): realloc() returned NULL");
			}
		}

		capa = newsize;
		ptr = addr;
	}
}

void XString::reserve (size_t bsize)
{
	// On prend en compte l'octet terminal qu'on ajoute syst�matiquement.
	expand (bsize - capa + 1);
}

XString::XString (const XString& s)
	: String(0, s.length()), capa(), growsize(DEFAULT_GROW_SIZE), buf()
{
	if (len < BUF_SIZE) {
		ptr = buf;
		capa = BUF_SIZE;
	} else {
		capa = len+1;
		ptr = allocate (capa);
	}
	memcpy (ptr, s.bytes(), len);
	ptr[len] = '\0';
}

XString::XString (const String& s)
	: String(0, s.length()), capa(), growsize(DEFAULT_GROW_SIZE), buf()
{
	if (len < BUF_SIZE) {
		ptr = buf;
		capa = BUF_SIZE;
	} else {
		capa = len+1;
		ptr = allocate (capa);
	}
	memcpy (ptr, s.bytes(), len);
	ptr[len] = '\0';
}

XString::XString (const char* s, size_t ln)
	: String(0, ln), capa(), growsize(DEFAULT_GROW_SIZE), buf()
{
	if (len < BUF_SIZE) {
		ptr = buf;
	} else {
		capa = len+1;
		ptr = allocate (capa);
	}
	//fprintf (stderr, "XString::XString(xs* sz): this %p, memcpy (%p '%s', %p '%s', %u)\n", this, ptr, ptr, s, s, len);
	memcpy (ptr, s, len);
	ptr[len] = '\0';
}


String& XString::adopt (const char* addr, size_t ln)
{
	return copyFrom (addr, ln);
}

String& XString::adopt (const String& src)
{
	return copyFrom (src);
}

XString& XString::clear()
{
	if (capa > 0) {
		*ptr = 0;
		len = 0;
	}
	return *this;
}


XString& XString::swap (XString& s)
{
	if (&s != this) {
		uint8_t tmp_buf[BUF_SIZE];
		size_t tmp_len = s.len;
		size_t tmp_siz = s.capa;
		size_t tmp_grow = s.growsize;

		if (s.ptr == s.buf) {
			if (ptr == buf) { // ni s ni moi en malloc
				::memcpy (tmp_buf, s.buf, BUF_SIZE);
				::memcpy (s.buf, buf, BUF_SIZE);
				::memcpy (buf, tmp_buf, BUF_SIZE);
			} else { // moi en malloc mais pas s
				::memcpy (buf, s.buf, BUF_SIZE);
				s.ptr = ptr;
				ptr = buf;
			}
		} else {
			if (ptr == buf) { // s malloc mais moi non
				::memcpy (s.buf, buf, BUF_SIZE);
				ptr = s.ptr;
				s.ptr = s.buf;
			} else { // s et moi en malloc
				uint8_t* tmp_ptr = s.ptr;
				s.ptr = ptr;
				ptr = tmp_ptr;
			}
		}

		s.len = len;
		s.capa = capa;
		s.growsize = growsize;
		len = tmp_len;
		capa = tmp_siz;
		growsize = tmp_grow;
	}
	return *this;
}


XString& XString::append (const char* addr, size_t sz)
{
	if (sz > 0) {
		if (available() < sz+1) {
			expand (sz+1);
		}

		memmove (ptr+len, addr, sz);
		len += sz;

		*(ptr+len) = '\0';
	}

	return *this;
}

XString& XString::append (const uint8_t* addr, size_t sz)
{
	return append (reinterpret_cast<const char*>(addr), sz);
}


XString& XString::appendChar (char c)
{
	if (available() < 2) {
		expand (2);
	}

	*(ptr+len++) = (uint8_t) c;
	*(ptr+len) = '\0';

	return *this;
}

XString& XString::appendInt (int v)
{
	char buf[128];
	size_t size = snprintf (buf, sizeof(buf), "%i", v);

	return append (buf, size);
}

XString& XString::appendInt32 (int32_t v)
{
	char buf[128];
	size_t size = snprintf (buf, sizeof(buf), "%ld", (long) v);

	return append (buf, size);
}

XString& XString::appendUint32 (uint32_t v)
{
	char buf[128];
	size_t size = snprintf (buf, sizeof(buf), "%lu", (unsigned long) v);

	return append (buf, size);
}

XString& XString::appendInt64 (int64_t v)
{
	char buf[128];
#if (defined(BITS) && BITS == 64)
	size_t size = snprintf (buf, sizeof(buf), "%ld", v);
#else
	size_t size = snprintf (buf, sizeof(buf), "%lld", v);
#endif
	return append (buf, size);
}

XString& XString::appendUint64 (uint64_t v)
{
	char buf[128];
#if (defined(BITS) && BITS == 64)
	size_t size = snprintf (buf, sizeof(buf), "%lu", v);
#else
	size_t size = snprintf (buf, sizeof(buf), "%llu", v);
#endif
	return append (buf, size);
}


XString& XString::ltrim()
{
	uint8_t* lptr = ptr;
	uint8_t* endptr = ptr+len-1;
	size_t newlen = len;

	while (lptr <= endptr && isspace (static_cast<int>(*lptr))) {
		++lptr;
		--newlen;
	}

	if (newlen == 0) {
		*buf = '\0';
		if (ptr != buf) {
			release (ptr);
			ptr = buf;
		}
	} else {
		memmove (ptr, lptr, newlen);
		ptr[newlen] = '\0';
	}
	len = newlen;

	return *this;
}

XString& XString::rtrim()
{
	uint8_t* rptr = ptr+len-1;
	size_t newlen = len;

	while (rptr >= ptr && isspace (static_cast<int>(*rptr))) {
		--rptr;
		--newlen;
	}

	*(rptr+1) = '\0';
	len = newlen;

	return *this;
}

XString& XString::trim()
{
	rtrim();
	return ltrim();
}

XString& XString::copyFrom (const char* s, size_t slen)
{
	size_t avail = available();

	if (avail < slen) {
		expand (slen-avail+1);
	}

	memmove (ptr, s, slen);
	*(ptr+slen) = 0;
	len = slen;

	return *this;
}

XString& XString::copyFromChar (char c)
{
	if (ptr == 0) {
		ptr = buf;
		capa = BUF_SIZE;
	}

	*ptr = (uint8_t)c;
	len = 1;

	return *this;
}

XString& XString::resize (size_t nbchars)
{
	if (UNLIKELY(nbchars >= capacity())) {
		ERRF ("XString: cannot adjust length to %lu, which is reater than capacity (%lu).", (unsigned long)nbchars, (unsigned long) capacity());
	} else {
		*(ptr+nbchars) = 0;
		len = nbchars;
	}

	return *this;
}

XString& XString::toUppercase()
{
	uint8_t* myptr = ptr;
	uint8_t* end = ptr+len;

	while (myptr < end) {
		*myptr = toupper((int)*myptr);
		++myptr;
	}
	return *this;
}

XString& XString::toLowercase()
{
	uint8_t* myptr = ptr;
	uint8_t* end = ptr+len;

	while (myptr < end) {
		*myptr = tolower((int)*myptr);
		++myptr;
	}
	return *this;
}


XString& XString::sprintf (const char* fmt, ...)
{
	va_list ap;
	int i;
	int newlen;
	size_t fmtlen = ::strlen (fmt);

	// On essaye de prendre une taille de d�part ...
	if (capacity() < fmtlen) {
		reserve (fmtlen+64);
	}

	for (i = 0; i < 2; ++i) {
		va_start (ap, fmt);
		newlen = vsnprintf ((char*)ptr, capacity(), fmt, ap);
		va_end (ap);

		if (newlen >= (int)capa) { // Pas assez de place...
			reserve (newlen);
		} else {
			break;
		}
	}

	if (i >= 2 || newlen == -1) {
		THROW ("XString::sprintf(): vsnprintf() failed.");
	} else {
		len = newlen;
	}

	return *this;
}

XString& XString::parseInt (int v)
{
	return this->sprintf("%d", v);
}

XString& XString::parseInt32 (int32_t v)
{
	return this->sprintf("%d", v);
}

XString& XString::parseUint32 (uint32_t v)
{
	return this->sprintf("%u", v);
}

XString& XString::parseInt64 (int64_t v)
{
#if (defined(BITS) && BITS == 64)
	return this->sprintf("%ld", v);
#else
	return this->sprintf("%lld", v);
#endif
}

XString& XString::parseUint64 (uint64_t v)
{
#if (defined(BITS) && BITS == 64)
	return this->sprintf("%lu", v);
#else
	return this->sprintf("%llu", v);
#endif
}

XString& XString::parseFloat (double v)
{
	return this->sprintf("%g", v);
}

XString& XString::operator << (double val)
{
	char buf[256];
	size_t sz = snprintf (buf, sizeof(buf),"%g", val);

	append (buf, sz);
	return *this;
}

} //namespace Fianet
