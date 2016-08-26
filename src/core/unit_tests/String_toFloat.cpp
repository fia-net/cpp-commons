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

// Nombres au format incorrect
TEST (StringTest, toFloat_InvalidNumberFormat)
{
	EXPECT_THROW (CSTR("").toFloat(), NumberFormatError);
	EXPECT_THROW (CSTR("abc").toFloat(), NumberFormatError);
	EXPECT_THROW (CSTR("+56bc").toFloat(), NumberFormatError);
	EXPECT_THROW (CSTR("0xerror").toFloat(), NumberFormatError);
	EXPECT_THROW (CSTR("-500\0000.50").toFloat(), NumberFormatError);
	EXPECT_THROW (CSTR("0.5 ").toFloat(), NumberFormatError);
}

// Nombres au format correct
TEST (StringTest, toFloat_ValidNumberFormat)
{
	EXPECT_NO_THROW (CSTR("0").toFloat());
	EXPECT_NO_THROW (CSTR("0.0").toFloat());
	EXPECT_NO_THROW (CSTR("-0.0").toFloat());
}

// Test des valeurs de conversions
TEST (StringTest, toFloat_ConversionCorrectness)
{
	EXPECT_EQ (0.0, String("0").toFloat());
	EXPECT_EQ (0.0, String("0.0").toFloat());
	EXPECT_EQ (0.0, String("0.0000").toFloat());
	EXPECT_EQ (0.0, String("-0.0").toFloat());
	EXPECT_EQ (-1.0, String("-1.0").toFloat());
	EXPECT_EQ (1.0, String("1.0").toFloat());
	EXPECT_EQ (1.5, String("1.500000").toFloat());
	EXPECT_EQ (-1.5, String("-1.500000").toFloat());
	EXPECT_EQ (1.10, String("1.10").toFloat());
	EXPECT_EQ (11.5, String("1.15e01").toFloat());
}

