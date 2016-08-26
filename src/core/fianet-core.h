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
#ifndef FIANET_CORE_H
#define FIANET_CORE_H

#define __STDC_LIMIT_MACROS 1

#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>

#if (defined(__sparc__) && __sparc__ == 1)
	#define CPU_IS_BIG_ENDIAN	1
#elif (defined(__i386__) && __i386__ == 1)
	#define CPU_IS_LITTLE_ENDIAN	1
	#define ARCH_IS_32BIT
#elif (defined(__x86_64__) && __x86_64__ == 1)
	#define CPU_IS_LITTLE_ENDIAN	1
	#define ARCH_IS_64BIT
#else
	#error "Unknown CPU ! Please fix endianness"
#endif


#ifdef CPU_IS_LITTLE_ENDIAN
	#define INT16_BYTE0(c)	(c & 0xFF)
	#define INT16_BYTE1(c)	((c>>8) & 0xFF)
#else
	#define INT16_BYTE0(c)	((c>>8) & 0xFF)
	#define INT16_BYTE1(c)	(c & 0xFF)
#endif

#define SWAP32B(a) ( (((a) & 0xFF) << 24) \
                       + (((a) & 0xFF00) << 8) \
                       + (((a) & 0xFF0000) >> 8) \
                       + (((a) & 0xFF000000) >> 24) )

#ifndef UNUSED_PARAM
	#ifdef __GNUC__
		#define UNUSED_PARAM(p) p __attribute__((unused))
	#else
		#define UNUSED_PARAM(p)
	#endif
#endif

#ifndef NO_RETURN
	#ifdef __GNUC__
		#define NO_RETURN __attribute__((noreturn))
	#else
		#define NO_RETURN
	#endif
#endif

#define LIKELY(x)    __builtin_expect (!!(x), 1)
#define UNLIKELY(x)  __builtin_expect (!!(x), 0)

#ifdef CHECK_POINTERS
	#define CHECK_PTR(ptr)  if (!(ptr)) { THROWF ("%s(): Unexpected NULL pointer '%s'.", __FUNCTION__, #ptr); }
#else
	#define CHECK_PTR(ptr)
#endif


#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <unistd.h>

#include "Exception.h"
#include "String.h"
#include "XString.h"

#endif // FIANET_CORE_H
