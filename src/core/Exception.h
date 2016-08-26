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
#ifndef FIANET_EXCEPTION_H
#define FIANET_EXCEPTION_H

#include <stdarg.h>
#include <stdexcept>

#ifdef __cplusplus

namespace Fianet {

class Exception : public std::exception {
protected:
	static const int MESSAGE_SIZE = 1024;

 	int code;
	char message[MESSAGE_SIZE];

private:
	/// Copie interdite
	Exception& operator = (const Exception&);

public:
	virtual ~Exception() throw();
	Exception() throw();
	Exception (const Exception& e) throw();

	explicit Exception (int code) throw();
	explicit Exception (const char* s) throw();
	explicit Exception (int code, const char* s) throw();

	int getCode() const throw() {
		return code;
	}

	virtual const char* getMessage() const throw() {
		return message;
	}

	virtual const char* what() const throw() {
		return message;
	}

	virtual Exception& addprefix (const char* prefix) throw();
	virtual Exception& addtext (const char* text) throw();
	virtual Exception& setCode (int code) throw();
	virtual Exception& setMessage (const char* msg) throw();
};


struct NumberError : public Exception {
	NumberError() : Exception() 
	{ }
	NumberError (const char* msg) : Exception(msg) 
	{ }
};
struct NumberFormatError : public NumberError {
	NumberFormatError() : NumberError("NumberFormatError")
	{ }
	NumberFormatError (const char* msg) : NumberError(msg)
	{ }
};
struct NumberRangeError : public NumberError {
	NumberRangeError() : NumberError("NumberRangeError")
	{ }
	NumberRangeError(const char* msg) : NumberError(msg)
	{ }
};

extern "C" {
#endif /* __cplusplus */

void throwError (const char* msg) throw (Fianet::Exception) __attribute__((noreturn));
void throwErrorf (int code, const char* fmt, ...) throw (Fianet::Exception) __attribute__((noreturn));
void throwException (const char* filename, int line, const char* msg) throw (Fianet::Exception) __attribute__((noreturn));
void throwExceptionf (const char* filename, int line, const char* fmt, ...) throw (Fianet::Exception) __attribute__((noreturn));

#ifdef __cplusplus

} // extern "C"

} // namespace Fianet

#endif

#define DEFAULT_EXCEPTION_CODE 0

#define ERR(msg)			throwError (msg)
#define ERRF(fmt, ...)		throwErrorf (DEFAULT_EXCEPTION_CODE, fmt, __VA_ARGS__)
#define ERRCF(code, fmt, ...) throwErrorf(code, fmt, __VA_ARGS__)
#define THROW(msg)			throwException (__FILE__, __LINE__, msg)
#define THROWF(fmt, ...)	throwExceptionf (__FILE__, __LINE__, fmt, __VA_ARGS__)

#endif // FIANET_EXCEPTION_H
