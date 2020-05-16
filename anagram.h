/* Copyright (c) 2020 Gabriel Wernersbach Farinas
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __ANAGRAM__
#define __ANAGRAM__

#ifdef USE_SIMD
#include <emmintrin.h>
#include <immintrin.h>
#include <tmmintrin.h>
#include <xmmintrin.h>
#else
#include "macros.h"
#endif

#include <bitset>
#include <fstream>
#include <iostream>
#include <list>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

//#define SHOW_DEBUG
//#define IGNORE_WORDS_WITH_LESS_LETTERS
#define USE_PARALLEL

// guess about max anagrams per line
// const int MAX_ANAGRAMS = 20;

#ifdef USE_SIMD
void
print_chars(const char* name, __m256i ma);
__m256i
break_chars(const std::string& name);
void
consume_chars(unsigned int index,
              std::string& output,
              __m256i original,
              __m256i consume);

#ifdef USE_PARALLEL
void
generateAnagramSimdParallel(const char* name);
#else  // USE_PARALLEL
void
generateAnagramSimd(const char* name);
#endif // USE_PARALLEL
void
freeBitmap();
#else // USE_SIMD
unsigned int
break_chars(const std::string& name, ABCDEFG_DEC_REF);
bool
insertBits(const char* word, int targetBits);
void
consume_chars(unsigned int index,
              std::string& output,
              ABCDEFG_DEC,
              _ABCDEFG_DEC);
#ifdef USE_PARALLEL
void
generateAnagramParallel(const char* name);
#else  // USE_PARALLEL
void
generateAnagram(const char* name);
#endif // USE_PARALLEL
#endif // USE_SIMD

void
generateDictionaryBits(const char* filename, const char* targetString);

#endif //__ANAGRAM__
