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
#include "fianet-core.h"

using namespace Fianet;

namespace {

TEST (StringTest, substr_1arg_works)
{
	String str("0123456789abcdef", 16);

	// Cas classiques
	EXPECT_EQ (str, str.substr(0));
	EXPECT_EQ (CSTR("123456789abcdef"), str.substr(1));
	EXPECT_EQ (CSTR("f"), str.substr(15));
	EXPECT_EQ (String::blank(), str.substr(16));
	EXPECT_EQ (String::blank(), str.substr(100));

	// start négatif : départ depuis length()-start
	EXPECT_EQ (CSTR("f"), str.substr(-1));
	EXPECT_EQ (CSTR("123456789abcdef"), str.substr(-15));
	EXPECT_EQ (str, str.substr(-16));
	EXPECT_EQ (String::blank(), str.substr(-100));
}

TEST (StringTest, substring_2args_works)
{
	String str("0123456789abcdef", 16);

	// Cas classiques
	EXPECT_EQ (String::blank(), str.substr(0, 0));
	EXPECT_EQ (CSTR("0"), str.substr(0, 1));
	EXPECT_EQ (CSTR("1"), str.substr(1, 1));
	EXPECT_EQ (str, str.substr(0, 16));
	EXPECT_EQ (CSTR("abcdef"), str.substr(10, 6));

	// start négatif : départ depuis length()-start
	EXPECT_EQ (String::blank(), str.substr(-1, 0));
	EXPECT_EQ (CSTR("f"), str.substr(-1, 1));
	EXPECT_EQ (str, str.substr(-16, 16));
	EXPECT_EQ (CSTR("abcdef"), str.substr(-6, 6));
	EXPECT_EQ (String::blank(), str.substr(-1, -1));

	// Test hors limites
	EXPECT_EQ (str, str.substr(0, 20));
	EXPECT_EQ (String::blank(), str.substr(200, 20));
	EXPECT_EQ (String::blank(), str.substr(-200, 200));
	EXPECT_EQ (String::blank(), str.substr(200, -200));
}


}
