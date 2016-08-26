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
#include "Exception.h"

#include <stdarg.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>

namespace Fianet {

Exception::~Exception() throw()
{
}

Exception::Exception() throw()
	: code(0), message()
{
	*message = 0;
}

Exception::Exception (int c) throw()
	: code(c), message()
{
	*message = 0;
}

Exception::Exception (const Exception& e) throw()
	: code(e.code), message()
{
	if (&e != this) {
		snprintf (message, sizeof(message)/sizeof(char), "%s", e.message);
	}
}

Exception::Exception (const char* s) throw()
	: code(0), message()
{
	if (s) {
		snprintf (message, sizeof(message)/sizeof(char), "%s", s);
	} else {
		*message = 0;
	}
}

Exception::Exception (int code_, const char* s) throw()
	: code(code_), message()
{
	if (s) {
		snprintf (message, sizeof(message)/sizeof(char), "%s", s);
	} else {
		*message = 0;
	}
}

Exception& Exception::addprefix (const char* prefix) throw()
{
	char tmp[MESSAGE_SIZE];
	
	snprintf (tmp, sizeof(tmp), "%s%s", prefix, message);
	strcpy (message, tmp);

	return *this;
}

Exception& Exception::addtext (const char* text) throw()
{
	snprintf (message+strlen(message), (sizeof(message)-strlen(message)), "%s", text);
	return *this;
}

Exception& Exception::setMessage(const char* msg) throw()
{
	snprintf (message, sizeof(message), "%s", msg);
	return *this;
}

Exception& Exception::setCode (int code_) throw()
{
	code = code_;
	return *this;
}

void throwException (const char* fileName, int lineNumber, const char* msg) throw (Fianet::Exception)
{
	char buff[1024];
	snprintf (buff, sizeof(buff)/sizeof(char), "[%s:%d]: %s", fileName, lineNumber, msg);
	
	throw Exception (buff);
}

void throwExceptionf (const char* fileName, int lineNumber, const char* fmt, ...) throw (Fianet::Exception)
{
	char buff[1024];
	ssize_t sz;

	sz = snprintf (buff, sizeof(buff)/sizeof(char), "[%s:%d]: ", fileName, lineNumber);

	va_list ap;
	va_start (ap, fmt);
	vsnprintf (buff+sz, (sizeof(buff)/sizeof(char)) - sz, fmt, ap);
	va_end (ap);

	throw Fianet::Exception (buff);
}

void throwError (const char* msg) throw (Fianet::Exception)
{
	throw Fianet::Exception (msg);
}

void throwErrorf (int code, const char* fmt, ...) throw (Fianet::Exception)
{
	char buff[1024];
	va_list ap;

	va_start (ap, fmt);
	vsnprintf (buff, sizeof(buff)/sizeof(char), fmt, ap);
	va_end (ap);

	throw Fianet::Exception (code, buff);
}

} // namespace Fianet

