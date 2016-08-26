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
#ifndef FIANET_XSTRING_H
#define FIANET_XSTRING_H

#include "fianet-core.h"

#if defined(__GNUC__)
  #define FORMAT_LIKE_PRINTF __attribute__ ((format (printf, 2, 3)))
#endif


namespace Fianet {

/**
 * @class XString
 * eXtensible Strings class.
 *
 * This is the "read/write" string buffer class.
 *
 * Supports automatic re-allocation of its internal buffer. Uses a simple form
 * of "short string optimization", in the sense that a small internal buffer
 * can handle short strings without allocating heap memory.
 *
 * - Unlike its parent, every XString instance constructed from some data gets
 * an immeditae copy of that data. No XString instance share the same data
 * pointers.
 * - Every XString instance is also guaranteed to be NUL-terminated
 * because an extra NUL byte is automatically appended to the buffer. This
 * extra byte is not counted in the string length().
 *
 * Heap allocations occur by multiples of 256 bytes (e.g. when 256 * 2 bytes
 * will be allocated when 257 bytes are needed). The value of 256 can be
 * modified for each instance.
 *
 * @see String
 */
class XString : public String {
private:
	/// By default, heap allocations are done by blocks of 256 bytes.
	static const size_t DEFAULT_GROW_SIZE = 256;
	/// Short string buffer size.
	static const size_t BUF_SIZE = 16;

	/// Total size of our buffer (including heap alloc)
	size_t capa;

	/// Our buffer expands by multiples of this value.
	size_t growsize;

	/// short string internal buffer.
	uint8_t buf[BUF_SIZE];

	/**
	 * expands buffer on the heap.
	 * @param neededsize the number of additional bytes requested.
	 * After a call to this method, the XString capacity() is
	 * the smallest multiple of (this->grow_size) larger than neededsize.
	 */
	void expand (size_t neededsize);

	/**
	 * See if the current capacity matches a size.
	 *
     * @param thesize the size to check.
     * @return true if capacity() >= thesite, false if not.
     */
	bool sizeFitsBuffer (size_t thesize) const;

	/**
     * @return the number of remaining "unused" bytes in the buffer.
     */
	size_t available() const;

public:
	~XString();

	/**
	 * Empty string constructor.
     */
	XString();

	/*
	 * Copy constructor.
     *
	 * @param s the source instance. Its data is copied in the constructed
	 * object.
	 */
 	XString (const XString& s);

	/**
	 * Constructs an XString by duplicating a String object content.
	 *
	 * @param s the source string to get a copy from.
	 */
	XString (const String& s);

	/**
	 * Constructs an XString from a pointer and a length. Useful for representing
	 * a "dynamic" byte buffer. The source data is copied in the XString buffer,
	 * which is reallocated as needed.
	 *
	 * @param addr the data pointer.
	 * @param len the data length in bytes.
	 */
	XString (const char* addr, size_t len);

	/**
	 * Updates the heap growth multiplier for the current instance.
	 * @param growsz the new heap growth multiplier.
	 */
	void setGrowSize (size_t growsz);


	/**
	 * @return the buffer size, in bytes. May be greater than length().
	 * Not really useful for String class.
	 *
	 * @see XString.
	 */
	size_t capacity() const;

	/**
	 * Capacity reservation.
	 * Makes sure that the buffer is large enough to handle the requested
	 * number of bytes. The buffer may be reallocated as needed.
     *
	 * @param bsize the requested capacity.
	 * @throw Exception when the heap memory allocation fails.
	 */
	void reserve (size_t bsize);

	/**
	 * Buffer swap
	 *
	 * Swaps the data buffers between two XString objects, with
	 * minimal data copy. Useful when an instance will be getting a large value
	 * from a temporary instance. A swap operation is then much efficient than
	 * copying the temporary data.
	 */
	 XString& swap (XString& s);

	/**
	 * Data assignment. Replace the contents of the current instance by
	 * a copy of the memory area given in parameters. The internal buffer is
	 * reallocated as needed.
	 *
	 * @param addr the data pointer.
	 * @param ln the data length.
	 * @return *this as a String.
	 */
	String& adopt (const char* addr, size_t ln);

	/**
	 * Data assignment from a String instance. Replace the contents of the
	 * current instance by a copy of the String buffer. The internal buffer is
	 * reallocated as needed.
	 *
	 * @param src the source String instance.
	 * @return *this as a String.
	 */
	String& adopt (const String& src);

	/**
	 * Data assignment. Replace the contents of the current instance by
	 * a copy of the memory area given in parameters. The internal buffer is
	 * reallocated as needed.
	 *
	 * @param addr the data pointer.
	 * @param ln the data length.
	 * @return *this.
	 * @see adopt()
	 */
	XString& copyFrom (const char* s, size_t len);

	/**
	 * Data assignment from a String instance. Replace the contents of the
	 * current instance by a copy of the String buffer. The internal buffer is
	 * reallocated as needed.
	 *
	 * @param src the source String instance.
	 * @return *this.
	 * @see adopt
	 */
	XString& copyFrom (const String& s);

	/**
	 * Data assignment from a char. Replace the contents of the current instance by
	 * the character value given.
	 *
	 * @param c the char value to assign.
	 * @return *this.
	 */
	XString& copyFromChar (char c);

	XString& parseInt (int v);
	XString& parseInt32 (int32_t v);
	XString& parseUint32 (uint32_t v);
	XString& parseInt64 (int64_t v);
	XString& parseUint64 (uint64_t v);
	XString& parseFloat (double v);

	/**
	 * Appends data.
	 * 
	 * Reallocates the internal buffer as needed. Then duplicates a memory block
	 * at the end of the internal buffer.
	 * 
	 * @param ptr the buffer address to append.
	 * @param ln the number of bytes to append.
	 */
	XString& append (const char* ptr, size_t ln);

	/**
	 * Appends data. uint8_t pointer variant.
	 *
	 * Reallocates the internal buffer as needed. Then duplicates a memory block
	 * at the end of the internal buffer.
	 *
	 * @param ptr the buffer address to append.
	 * @param ln the number of bytes to append.
	 */
	XString& append (const uint8_t* ptr, size_t ln);

	/**
	 * Appends data from a String.
	 *
	 * Reallocates the internal buffer as needed. Then duplicates the given
	 * String buffer at the end of the internal buffer.
	 *
	 * @param s the String to append.
	 */
	XString& append (const String& s);

	/**
	 * Appends data from a char.
	 *
	 * Reallocates the internal buffer as needed. Then appends the char value
	 * to the internal buffer.
	 *
	 * @param c the char value to append.
	 */
	XString& appendChar (char c);

	/**
	 * Appends a string representation of an integral value to the buffer.
	 *
	 * This function convert an integral value to its string representation,
	 * and appends that representation to the current buffer, which is
	 * reallocated as needed.
	 *
	 * @param v the integral value to convert and append.
	 */
	XString& appendInt (int v);

	/**
	 * Appends a string representation of an integral value to the buffer.
	 *
	 * This function convert an integral value to its string representation,
	 * and appends that representation to the current buffer, which is
	 * reallocated as needed.
	 *
	 * @param v the integral value to convert and append.
	 */
	XString& appendInt32 (int32_t v);

	/**
	 * Appends a string representation of an integral value to the buffer.
	 *
	 * This function convert an integral value to its string representation,
	 * and appends that representation to the current buffer, which is
	 * reallocated as needed.
	 *
	 * @param v the integral value to convert and append.
	 */
	XString& appendUint32 (uint32_t v);

	/**
	 * Appends a string representation of an integral value to the buffer.
	 *
	 * This function convert an integral value to its string representation,
	 * and appends that representation to the current buffer, which is
	 * reallocated as needed.
	 *
	 * @param v the integral value to convert and append.
	 */
	XString& appendInt64 (int64_t v);

	/**
	 * Appends a string representation of an integral value to the buffer.
	 *
	 * This function convert an integral value to its string representation,
	 * and appends that representation to the current buffer, which is
	 * reallocated as needed.
	 *
	 * @param v the integral value to convert and append.
	 */
	XString& appendUint64 (uint64_t v);

	/**
	 * Removes whitespaces at the beginning of the string.
	 *
	 * Moves the buffer content to the next non-whitespace character in the
	 * data. Changes the string length accordingly. No reallocation occurs.
	 * @return *this.
	 */
	XString& ltrim();

	/**
	 * Removes whitespaces at the end of the string.
	 *
	 * Decreases the length of the buffer until the last non-whitespace
	 * character in the data. Changes the string length accordingly.
	 * No reallocation occurs.
	 * @return *this.
	 */
	XString& rtrim();

	/**
	 * Removes whitespaces at the beginning and the end of the data.
	 * Changes the string length value accordingly. Data may be
	 * copied but not reallocated.
	 * @return *this.
	 */
	XString& trim();

	/**
	 * Sets the length to 0. After calling this
	 * method, the instance is equivalent to String::blank().
	 * @note does not release any allocated memory.
	 *
	 * @return *this.
	 */
	XString& clear();


	/**
	 * Adjusts the length() within the current buffer capacity.
	 *
	 * This method redefines the XString length() by simply changing the
	 * internal length member value, thus causing no memory reallocation or
	 * copy. A NUL character is guaranteed to be appended as usual.
	 *
     * @param len the adjusted length. Must be strictly less than the current
	 * capacity().
	 *
     * @return *this.
     */
	XString& resize (size_t len);


	/**
	 * Replaces all the characters in the buffer by their upper-case
	 * counterparts.
	 * @return *this
	 */
	XString& toUppercase();

	/**
	 * Replaces all the characters in the buffer by their lower-case
	 * counterparts.
	 * @return *this
	 */
	XString& toLowercase();


	/**
	 * Replaces the content of the instance by a list of arguments described
	 * by a format string, exactly like C's sprintf() function.
	 *
	 * The buffer may be reallocated as needed.
	 * 
	 * @param fmt the formating string.
	 * @param ... The variable arguments described by fmt.
	 * @return *this
	 * @see sprintf()
	 */
	XString& sprintf (const char* fmt, ...) FORMAT_LIKE_PRINTF;

	/**
	 * Assigment operator.
	 * The source data is duplicated.
	 *
     * @param s the String to assign.
     * @return *this
     */
	XString& operator = (const String& s);

	/**
	 * Appends a string.
	 * The source data is duplicated and appended to our internal buffer.
	 * A memory reallocation can occur.
	 *
     * @param s the String to append.
     * @return *this
     */
	XString& operator << (const String& s);

	/**
	 * @see appendInt32()
     * @param val
     * @return *this
     */
	XString& operator << (int32_t val);
	/**
	 * @see appendUint32()
     * @param val
     * @return *this
     */
	XString& operator << (uint32_t val);
	/**
	 * @see appendFloat()
     * @param val
     * @return *this
     */
	XString& operator << (double val);
};

inline XString& XString::operator = (const String& s)
{
	copyFrom(s);
	return *this;
}

inline size_t XString::capacity() const
{
	return capa;
}

inline void XString::setGrowSize (size_t growSize)
{
	growsize = growSize;
}

inline bool XString::sizeFitsBuffer (size_t sz) const
{
	return (sz <= BUF_SIZE);
}

inline size_t XString::available() const
{
	return (capacity() - length() - 1);
}

inline XString& XString::append (const String& s)
{
	return append (s.cstr(), s.length());
}

inline XString& XString::copyFrom (const String& s)
{
	return copyFrom (s.cstr(), s.length());
}

inline XString& XString::operator << (const String& s)
{
	return append (s);
}

inline XString& XString::operator << (int32_t val)
{
	return appendInt32(val);
}

inline XString& XString::operator << (uint32_t val)
{
	return appendUint32(val);
}

} //namespace Fianet

#endif // FIANET_XSTRING_H
