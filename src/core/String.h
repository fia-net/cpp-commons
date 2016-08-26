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
#ifndef FIANET_STRING_H
#define FIANET_STRING_H

#include "fianet-core.h"

#define CSTR(s)	String(s, (sizeof(s)/sizeof(char)-1))

namespace Fianet {

/**
 * @class String
 * Basic read-only string class. They basically are a char pointer and a length.
 * A String is "read-only" in the sense that no method can be used to modify
 * the data it points to. However, the data pointer and length can be modified
 * with some methods.
 * A String is not guaranteed to be NUL-terminated so  traditional C-string
 * functions useage is discouraged.
 *
 * This class can be seen as a "String view" or "String reference". It's handy
 * to be used for no-copy operations on character buffers. For example,
 * calling String::trim() does adjust the internal data pointer and length
 * properties, effectively "removing" the spaces found at the beginning
 * and the end of the buffer, but data will be copied or moved.
 *
 * String objects can handle static C strings (e.g. const char* str = "hello")
 * and therefore handle the trailing NUL character.
 */
class String {
protected:
	/// Address of our data.
	uint8_t* ptr;
	/// Number of bytes used by our data.
	size_t len;

public:
	/**
	 * Empty string.
	 */
	String();

	/**
	 * Constructs a String form a null-terminated C string. Should be used on
	 * static variables. Can be used as a view on local variables
	 * (char arrays), but the String instance accessors must not be called as
	 * soon as the local variable is no longer on the stack.
	 *
	 * @param c_str address of the C string to get a view on.
	 *
	 */
	String (const char* c_str);

	/**
	 * Constructs a String from a pointer and a length. Useful for representing
	 * a byte buffer. This buffer does not necessarily ends with a null byte.
	 *
	 * @param addr the data pointer.
	 * @param ln the data length in bytes.
	 */
	String (const char* addr, size_t ln);

	/**
	 * Copy constructor. The pointer and length are copied from the source
	 * object. The source object buffer content is *not* copied.
	 *
	 * @param s the source String.
	 */
	String (const String& s);

	/**
	 * Assignment. As with the copy constructor, the pointer and length
	 * are copied, but no copy is made of the pointer content.
	 *
	 * @param s the String to assign.
	 */
	String& operator = (const String& s);

	/**
	 * Destructs the current instance.
	 */
	virtual ~String();

	/**
	 * Convenient read-only pointer access. 
	 * @note Unlike std::string::c_str(), there is no guarantee to have a
	 * NUL-terminated string! Use with caution!
	 * @return the data pointer casted to a char*.
	 */
	const char* cstr() const;

	/**
	 * Convenient read-only pointer access.
	 * @return the data pointer casted to a uint8_t.
	 */
	const uint8_t* bytes() const;

	/**
	 * @return the buffer length in bytes.
	 */
	size_t length() const;

	/**
	 * Removes whitespaces at the beginning of the pointed data.
	 * 
	 * Shifts the buffer pointer to the next non-whitespace character in the
	 * data. Changes the pointer and length values accordingly.
	 * @return *this.
	 */
	virtual String& ltrim();

	/**
	 * Removes whitespaces at the end of the pointed string.
	 * 
	 * Decreases the length of the buffer until the last non-whitespace
	 * character in the data. Changes the pointer and length values accordingly.
	 * @return *this.
	 */
	virtual String& rtrim();

	/**
	 * Removes whitespaces at the beginning and the end of the data.
	 * Changes the pointer and length values accordingly.
	 * @return *this.
	 */
	virtual String& trim();

	/**
	 * Sets the length to 0, and the pointer to a NUL byte. After calling this
	 * method, the instance is equivalent to String::blank().
	 *
	 * @return *this.
	 */
	virtual String& clear();

	/**
	 * Sets the internal pointer and length to the provided values.
	 * @param src the data pointer.
	 * @param length the data length.
	 * @return *this.
	 */
	virtual String& adopt (const char* src, size_t length);

	/**
	 * Sets the internal pointer and length to the values from the String
	 * instance provided. Same as the assignment operator.
	 * @param src the String instance to get the values from.
	 * @return *this.
	 */
	virtual String& adopt (const String& src);

	/**
	 * Access a character at a given position with bounds checking.
	 * @param pos the position to get the character from. Must be included in
	 * the range [ 0 ... length() - 1]
	 * @return the character.
	 * @throw Exception when the position is out of bounds.
	 */
	char operator[] (size_t pos) const;

	/**
	 * Access a character at a given position with bounds checking.
	 * @param pos the position to get the character from. Must be included in
	 * the range [ 0 ... length() - 1]
	 * @return the character.
	 * @throw Exception when the position is out of bounds.
	 */
	char charAt (size_t pos) const;

	/**
	 * @return true if the data pointed by both strings is the same, using
	 * byte comparison if necessary.
	 */
	bool equals (const String& s) const;

	/**
	 * See if a char is present in the String data.
	 * @return true if c is found, false if not.
	 */
	bool containsChar (char c) const;

	/**
	 * See if current String data contains the data of an other String, using
	 * byte comparison if necessary.
	 * @param s the String that may be contained by *this instance.
	 * @return true if *this contains s, false if not.
	 */
	bool contains (const String& s) const;

	/**
	 * See if current String data starts with the same bytes than an 
	 * other String, using byte comparison if necessary.
	 *
	 * @param s the String to look for in *this instance.
	 * @return true if *this starts with s, false if not.
	 */
	bool startsWith (const String& s) const;

	/**
	 * See if current String data ends with the same bytes than an
	 * other String, using byte comparison if necessary.
	 *
	 * @param s the String to look for in *this instance.
	 * @return true if *this starts with s, false if not.
	 */
	bool endsWith (const String& s) const;


	/**
	 * Compares two Strings.
	 *
	 * This function performs a binary comparison of the byte data contained
	 * in the current instance buffer and in the given argument.
	 *
	 * @param s the String instance to compare to.
	 *
	 * @return 0 when the contents of both String objects are equal.
	 * @return a number > 0 when the first character that does not match
	 * has a greater value in the current instance than in s.
	 * @return a number &lt; 0 when the first character that does not match
	 * has a greater value in the current instance than in s.
	 *
	 * @see memcmp
	 */
	int compareTo (const String& s) const;

	/**
	 * Compares two Strings up to a given number of characters.
	 *
	 * This function performs a binary comparison of the byte data contained
	 * in the current instance buffer and in the given argument.
	 *
	 * @param s the String instance to compare to.
	 * @param nb the maximum number of bytes to compare.
	 *
	 * @return 0 when the contents of both String objects are equal.
	 * @return a number > 0 when the first character that does not match
	 * has a greater value in the current instance than in s.
	 * @return a number &lt; 0 when the first character that does not match
	 * has a greater value in the current instance than in s.
	 *
	 * @see memcmp
	 */
	int compareTo (const String& s, uint32_t nb) const;


	/**
	 * @return true if the data pointed by both strings is the same, using
	 * case-insensitive comparison if necessary.
	 */
	bool iequals (const String& s) const;

	/**
	 * See if current String data contains the data of an other String, using
	 * case-insensitive comparison.
	 * 
	 * @param s the String that may be contained by *this instance.
	 * @return true if *this contains s, false if not.
	 * @note results depends on the current locale.
	 */
	bool icontains (const String& s) const;

	/**
	 * See if current String data starts with the same bytes than an
	 * other String, using case-insensitive comparison.
	 *
	 * @param s the String to look for in *this instance.
	 * @return true if *this starts with s, false if not.
	 * @note results depends on the current locale.
	 */
	bool istartsWith (const String& s) const;

	/**
	 * See if current String data ends with the same bytes than an
	 * other String, using case-insensitive comparison.
	 *
	 * @param s the String to look for in *this instance.
	 * @return true if *this starts with s, false if not.
	 * @note results depends on the current locale.
	 * @note results depends on the current locale.
	 */
	bool iendsWith (const String& s) const;

	int icompareTo (const String& s, uint32_t nbChars) const;
	int icompareTo (const String& s) const;

	/**
	 * Get a substring with zero-copy.
	 *
	 * @param offset is the beginning offset of the substring. The substring will
	 *   - if offset is non negative, the extracted string begins at the [0+offset] position.
	 *   - if offset is negative, the substring begins at the [length()+offset] position (e.g. counting is made from the end of the String buffer).
	 *   - if offset is out of bounds (e.g. offset > length() or offset &lt; -length()), the returned String is empty (e.g. String::blank()).
	 *
	 * @param nb is the number of bytes of the desired substring, given that:
	 *   - If nb is zero, the returned substring is String::blank().
	 *   - If nb is non negative, the substring will contain at most nb bytes from the starting position.
	 *   - If nb is negative, the substring will contain at most (length() - nb) bytes.
	 *   - The calculated length cannot be larger than the String instance length, and cannot be negative.
	 *     It is adjusted as necessary.
	 *
	 * @return a String instance with the extracted substring, or String::blank().
	 */
	const String substr (int offset, int nb) const;

	/**
	 * Get a substring with zero-copy. The substring begins at a given position and
	 * includes all the bytes up to the end of the pointed data.
	 *
	 * @param offset is the beginning offset of the substring. The substring will
	 *   - If offset is non negative, the extracted string begins at the [0 + offset] position.
	 *   - If offset is negative, the substring begins at the [length() + offset] position (e.g. counting is made from the end of the String buffer).
	 *   - If offset is out of bounds (e.g. offset > length() or offset &lt; -length()), the returned String is empty (e.g. String::blank()).
	 * @return a String instance with the extracted substring, or String::blank().
	 */
	const String substr (int offset) const;

	/**
	 * Substring search.
	 *
	 * Gets the position of the first occurrence of a String within
	 * the current instance.
	 *
	 * @param s the String to look for in the current instance.
	 * @return the position of the matching byte sequence that is looked for,
	 * -1 if not found.
	 */
	ssize_t indexOf (const String& s) const;

	/**
	 * Character search.
	 *
	 * @param c the character to look for.
	 * @return the position of the first occurrence of c in the String
	 * data, -1 if not found.
	 */
	ssize_t indexOfChar (char c) const;

	/**
	 * Substring search from the end.
	 *
	 * Gets the position of the last occurrence of a String within
	 * the current instance.
	 *
	 * @param s the String to look for in the current instance.
	 * @return the last position of the 1st byte of s within the current instance
	 * data, -1 if not found.
	 */
	ssize_t lastIndexOf (const String& s) const;

	/**
	 * Character search.
	 *
	 * @param c the character to look for.
	 * @return the position of the last occurrence of c in the String
	 * data, -1 if not found.
	 */
	ssize_t lastIndexOfChar (char c) const;

	/**
	 * Converts the String data to an int value.
	 *
	 * The String content is interpreted as an integral number and returns the
	 * corresponding value. The base in which the number is written
	 * is determined automatically.
	 *
	 * @see strtol() and similar C functions.
	 *
	 * @return the integral value read from the String data.
	 * @throw NumberRangeError when the value cannot fit in the range of the
	 * desired type.
	 * @throw NumberFormatError if an invalid character was encountered during
	 * the conversion process.
	 */
	int toInt() const;

	/**
	 * Converts the String data to an int32_t value.
	 *
	 * The String content is interpreted as an integral number and returns the
	 * corresponding value. The base in which the number is written
	 * is determined automatically.
	 * 
	 * @see strtol() and similar C functions.
	 *
	 * @return the integral value read from the String data.
	 * @throw NumberRangeError when the value cannot fit in the range of the
	 * desired type.
	 * @throw NumberFormatError if an invalid character was encountered during
	 * the conversion process.
	 */
	int32_t toInt32() const;

	/**
	 * Converts the String data to an uint32_t value.
	 *
	 * The String content is interpreted as an integral number and returns the
	 * corresponding value. The base in which the number is written
	 * is determined automatically.
	 *
	 * @see strtol() and similar C functions.
	 *
	 * @return the integral value read from the String data.
	 * @throw NumberRangeError when the value cannot fit in the range of the
	 * desired type.
	 * @throw NumberFormatError if an invalid character was encountered during
	 * the conversion process.
	 */
	uint32_t toUint32() const;

	/**
	 * Converts the String data to an int64_t value.
	 *
	 * The String content is interpreted as an integral number and returns the
	 * corresponding value. The base in which the number is written
	 * is determined automatically.
	 *
	 * @see strtol() and similar C functions.
	 *
	 * @return the integral value read from the String data.
	 * @throw NumberRangeError when the value cannot fit in the range of the
	 * desired type.
	 * @throw NumberFormatError if an invalid character was encountered during
	 * the conversion process.
	 */
	int64_t toInt64() const;

	/**
	 * Converts the String data to an uint64_t value.
	 *
	 * The String content is interpreted as an integral number and returns the
	 * corresponding value. The base in which the number is written
	 * is determined automatically.
	 *
	 * @see strtol() and similar C functions.
	 *
	 * @return the integral value read from the String data.
	 * @throw NumberRangeError when the value cannot fit in the range of the
	 * desired type.
	 * @throw NumberFormatError if an invalid character was encountered during
	 * the conversion process.
	 */
	uint64_t toUint64() const;

	/**
	 * Converts the String data to a double value.
	 *
	 * The String content is interpreted as a floating point number and returns
	 * the corresponding value.
	 *
	 * @see strtod() and similar C functions.
	 *
	 * @return the floating point value read from the String data.
	 * @throw NumberRangeError when the value cannot fit in the range of the
	 * desired type.
	 * @throw NumberFormatError if an invalid character was encountered during
	 * the conversion process.
	 */
	double toFloat() const;


	/**
	 * @return a blank String with 0 length. Convenience function, the String()
	 * constructor can also be used.
	 */
	static const String& blank();


	/**
	 * @return a reference to a String containing only CR and LF characters.
	 * ("\r\n").
	 */
	static const String& CRLF();

	/**
	 * Allows Strings to be used in STL containers, used for value comparison.
	 */
	struct Comparator {

	 	bool operator() (const String& p1, const String& p2) const {
			return (p1.compareTo(p2) < 0);
		}
		bool starts (const String& p1, const String& s2) const {
			return p1.startsWith(s2);
		}

	};

	/**
	 * Allows Strings to be used in STL containers, used for case-insensitive
	 * value comparison.
	 */
	struct IComparator {
	 	bool operator() (const String& p1, const String& p2) const {
			return (p1.icompareTo(p2) < 0);
		}
		bool starts (const String& p1, const String& s2) const {
			return p1.istartsWith(s2);
		}
	};
};

inline String::String (const char* c_str)
	: ptr((uint8_t*)c_str), len(::strlen(c_str))
{ }

inline String& 	String::operator = (const String& s) {
	return this->adopt(s);
}

inline const char* String::cstr() const {
	return (const char*) ptr;
}

inline const uint8_t* String::bytes() const {
	return ptr;
}

inline size_t String::length() const {
	return len;
}

inline char String::charAt (uint32_t pos) const {
	if (pos >= (uint32_t) length()) {
		THROWF ("String::charAt(): index '%d' out of bounds.", (unsigned long) pos);
	}
	return (char) (*(ptr+pos));
}

inline char String::operator [] (uint32_t pos) const {
	return charAt(pos);
}

inline String& String::clear() {
	adopt(blank());
	return *this;
}

inline bool String::containsChar (char c) const {
	return (indexOfChar (c) >= 0);
}

inline bool operator == (const String& s1, const String& s2) {
	return (s1.equals(s2));
}

inline bool operator != (const String& s1, const String& s2) {
	return (!s1.equals(s2));
}

inline bool operator > (const String& s1, const String& s2) {
	return (s1.compareTo(s2) > 0);
}

inline bool operator >= (const String& s1, const String& s2) {
	return (s1.compareTo(s2) >= 0);
}

inline bool operator < (const String& s1, const String& s2) {
	return (s1.compareTo(s2) < 0);
}

inline bool operator <= (const String& s1, const String& s2) {
	return (s1.compareTo(s2) <= 0);
}

/**
 * Looks for the 1st occurrence of needle in haystack.
 * @return the address of the 1st haystack byte sequence that matches needle.
 * @return NULL if needle is not found in haystack.
 */
uint8_t* memfind (const void* haystack, size_t haystack_len, const void* needle, size_t needle_len);

/**
 * Looks for the 1st occurrence of needle in haystack. case-insensitive variant.
 * @return the address of the 1st haystack byte sequence that matches needle.
 * @return NULL if needle is not found in haystack.
 */
uint8_t* memifind (const void* haystack, size_t haystack_len, const void* needle, size_t needle_len);


/**
 * Compares two byte buffers in a "case-insensitive" way.
 * @see memcmp()
 */
int memicompare (const void* s1, const void* s2, size_t sz);


} // namespace Fianet

#endif // FIANET_STRING_H
