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
#include <limits.h>
#include "fianet-core.h"

using namespace Fianet;

void toInt_expect_NumberFormatError (const Fianet::String& val)
{
	EXPECT_THROW (val.toInt(), NumberFormatError);
	EXPECT_THROW (val.toInt32(), NumberFormatError);
	EXPECT_THROW (val.toInt64(), NumberFormatError);
	EXPECT_THROW (val.toUint32(), NumberFormatError);
	EXPECT_THROW (val.toUint64(), NumberFormatError);
}

void toInt_expect_NoFormatError (const String& val)
{
	EXPECT_NO_THROW (val.toInt());
	EXPECT_NO_THROW (val.toInt32());
	EXPECT_NO_THROW (val.toInt64());
	EXPECT_NO_THROW (val.toUint32());
	EXPECT_NO_THROW (val.toUint64());
}

void toInt_test_allConversions (const String& str, int value)
{
	EXPECT_EQ (value, str.toInt());
	EXPECT_EQ (value, str.toInt32());
	EXPECT_EQ (value, str.toInt64());

	// Conversions of negative numbers to unsigned types throw NumberRangeError
	if (value >= 0) {
		EXPECT_EQ ((uint32_t)value, str.toUint32());
		EXPECT_EQ ((uint64_t)value, str.toUint64());
	} else {
		EXPECT_THROW (str.toUint32(), NumberRangeError);
		EXPECT_THROW (str.toUint64(), NumberRangeError);
	}
}

TEST (StringTest, toInt_InvalidNumberFormat)
{
	SCOPED_TRACE("from toInt_InvalidNumberFormat");
	toInt_expect_NumberFormatError (CSTR(""));
	toInt_expect_NumberFormatError (CSTR("abc"));
	toInt_expect_NumberFormatError (CSTR("+56bc"));
	toInt_expect_NumberFormatError (CSTR("0xerror"));
	toInt_expect_NumberFormatError (CSTR("0.50"));
	toInt_expect_NumberFormatError (CSTR("-500\0000.50"));
}

TEST (StringTest, toInt_ValidNumberFormat)
{
	SCOPED_TRACE("from toInt_ValidNumberFormat");
	toInt_expect_NoFormatError (CSTR("0"));
	toInt_expect_NoFormatError (CSTR("123456789"));
	toInt_expect_NoFormatError (CSTR("0x123456"));

}

TEST (StringTest, toInt_ConversionCorrectness)
{
	int imax = INT_MAX;
	int imin = INT_MIN;
	int32_t i32max= INT32_MAX;
	int32_t i32min = INT32_MIN;
	uint32_t ui32max = UINT32_MAX;
	int64_t i64max= INT64_MAX;
	int64_t i64min = INT64_MIN;
	uint64_t ui64max = UINT64_MAX;

	String int_max("2147483647", 10);
	String int_min("-2147483648", 11);
	String int32_max("2147483647", 10);
	String int32_min("-2147483648", 11);
	String uint32_max("4294967295", 10);
	String int64_max("9223372036854775807", 19);
	String int64_min("-9223372036854775808", 20);
	String uint64_max("18446744073709551615", 20);

	toInt_test_allConversions (CSTR("0"), 0);
	toInt_test_allConversions (CSTR("10"), 10);
	toInt_test_allConversions (CSTR("-10"), -10);
	toInt_test_allConversions (CSTR("-65535"), -65535);

	EXPECT_EQ (imax, int_max.toInt());
	EXPECT_EQ (imin, int_min.toInt());

	EXPECT_EQ (i32max, int32_max.toInt32());
	EXPECT_EQ (i32min, int32_min.toInt32());

	EXPECT_EQ (i64max, int64_max.toInt64());
	EXPECT_EQ (i64min, int64_min.toInt64());

	EXPECT_EQ (ui32max, uint32_max.toUint32());
	EXPECT_EQ (ui64max, uint64_max.toUint64());

	EXPECT_NO_THROW (int32_max.toInt());
	EXPECT_NO_THROW (int32_min.toInt());
	EXPECT_THROW (uint32_max.toInt(), NumberRangeError);
	EXPECT_THROW (int64_max.toInt(), NumberRangeError);
	EXPECT_THROW (int64_min.toInt(), NumberRangeError);
	EXPECT_THROW (uint64_max.toInt(), NumberRangeError);

	EXPECT_NO_THROW (int32_max.toInt32());
	EXPECT_NO_THROW (int32_min.toInt32());
	EXPECT_THROW (uint32_max.toInt32(), NumberRangeError);
	EXPECT_THROW (int64_max.toInt32(), NumberRangeError);
	EXPECT_THROW (int64_min.toInt32(), NumberRangeError);
	EXPECT_THROW (uint64_max.toInt32(), NumberRangeError);

	EXPECT_NO_THROW (int32_max.toUint32());
	EXPECT_THROW (int32_min.toUint32(), NumberRangeError);
	EXPECT_NO_THROW (uint32_max.toUint32());
	EXPECT_THROW (int64_max.toUint32(), NumberRangeError);
	EXPECT_THROW (int64_min.toUint32(), NumberRangeError);
	EXPECT_THROW (uint64_max.toUint32(), NumberRangeError);

	EXPECT_NO_THROW (int32_max.toInt64());
	EXPECT_NO_THROW (int32_min.toInt64());
	EXPECT_NO_THROW (uint32_max.toInt64());
	EXPECT_NO_THROW (int64_max.toInt64());
	EXPECT_NO_THROW (int64_min.toInt64());
	EXPECT_THROW (uint64_max.toInt64(), NumberRangeError);

	EXPECT_NO_THROW (int32_max.toUint64());
	EXPECT_THROW (int32_min.toUint64(), NumberRangeError);
	EXPECT_NO_THROW (uint32_max.toUint64());
	EXPECT_NO_THROW (int64_max.toUint64());
	EXPECT_THROW (int64_min.toUint64(), NumberRangeError);
	EXPECT_NO_THROW (uint64_max.toUint64());
}

TEST (StringTest, toInt_ConversionCorrectnessWitCopy)
{
	int imax = INT_MAX;
	int imin = INT_MIN;
	int32_t i32max= INT32_MAX;
	int32_t i32min = INT32_MIN;
	uint32_t ui32max = UINT32_MAX;
	int64_t i64max= INT64_MAX;
	int64_t i64min = INT64_MIN;
	uint64_t ui64max = UINT64_MAX;

	String int_max("2147483647", 10);
	String int_min("-2147483648", 11);
	String int32_max("2147483647", 10);
	String int32_min("-2147483648", 11);
	String uint32_max("4294967295", 10);
	String int64_max("9223372036854775807", 19);
	String int64_min("-9223372036854775808", 20);
	String uint64_max("18446744073709551615", 20);

	toInt_test_allConversions (String("0"), 0);
	toInt_test_allConversions (String("10"), 10);
	toInt_test_allConversions (String("-10"), -10);
	toInt_test_allConversions (String("-65535"), -65535);

	EXPECT_EQ (imax, int_max.toInt());
	EXPECT_EQ (imin, int_min.toInt());

	EXPECT_EQ (i32max, int32_max.toInt32());
	EXPECT_EQ (i32min, int32_min.toInt32());

	EXPECT_EQ (i64max, int64_max.toInt64());
	EXPECT_EQ (i64min, int64_min.toInt64());

	EXPECT_EQ (ui32max, uint32_max.toUint32());
	EXPECT_EQ (ui64max, uint64_max.toUint64());

	EXPECT_NO_THROW (int32_max.toInt());
	EXPECT_NO_THROW (int32_min.toInt());
	EXPECT_THROW (uint32_max.toInt(), NumberRangeError);
	EXPECT_THROW (int64_max.toInt(), NumberRangeError);
	EXPECT_THROW (int64_min.toInt(), NumberRangeError);
	EXPECT_THROW (uint64_max.toInt(), NumberRangeError);

	EXPECT_NO_THROW (int32_max.toInt32());
	EXPECT_NO_THROW (int32_min.toInt32());
	EXPECT_THROW (uint32_max.toInt32(), NumberRangeError);
	EXPECT_THROW (int64_max.toInt32(), NumberRangeError);
	EXPECT_THROW (int64_min.toInt32(), NumberRangeError);
	EXPECT_THROW (uint64_max.toInt32(), NumberRangeError);

	EXPECT_NO_THROW (int32_max.toUint32());
	EXPECT_THROW (int32_min.toUint32(), NumberRangeError);
	EXPECT_NO_THROW (uint32_max.toUint32());
	EXPECT_THROW (int64_max.toUint32(), NumberRangeError);
	EXPECT_THROW (int64_min.toUint32(), NumberRangeError);
	EXPECT_THROW (uint64_max.toUint32(), NumberRangeError);

	EXPECT_NO_THROW (int32_max.toInt64());
	EXPECT_NO_THROW (int32_min.toInt64());
	EXPECT_NO_THROW (uint32_max.toInt64());
	EXPECT_NO_THROW (int64_max.toInt64());
	EXPECT_NO_THROW (int64_min.toInt64());
	EXPECT_THROW (uint64_max.toInt64(), NumberRangeError);

	EXPECT_NO_THROW (int32_max.toUint64());
	EXPECT_THROW (int32_min.toUint64(), NumberRangeError);
	EXPECT_NO_THROW (uint32_max.toUint64());
	EXPECT_NO_THROW (int64_max.toUint64());
	EXPECT_THROW (int64_min.toUint64(), NumberRangeError);
	EXPECT_NO_THROW (uint64_max.toUint64());
}

