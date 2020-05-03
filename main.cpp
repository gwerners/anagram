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
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility> // std::pair
#include <vector>

#ifdef USE_SIMD
#include <emmintrin.h>
#include <immintrin.h>
#include <tmmintrin.h>
#include <xmmintrin.h>
#else
#include "macros.h"
#endif

//#define SHOW_DEBUG
//#define IGNORE_WORDS_WITH_LESS_LETTERS

std::vector<std::string> palavras;
#ifdef USE_SIMD
__m256i* bitmap = nullptr;
#else
std::vector<unsigned int> bitmap;

enum CharBits
{
    a = 0,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z
};
#endif
#ifdef USE_SIMD
void
print_chars(const char* name, __m256i ma)
{
    printf(
      "m_ %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x - "
      "%s\n",
      _mm256_extract_epi8(ma, 31),
      _mm256_extract_epi8(ma, 30),
      _mm256_extract_epi8(ma, 29),
      _mm256_extract_epi8(ma, 28),
      _mm256_extract_epi8(ma, 27),
      _mm256_extract_epi8(ma, 26),
      _mm256_extract_epi8(ma, 25),
      _mm256_extract_epi8(ma, 24),
      _mm256_extract_epi8(ma, 23),
      _mm256_extract_epi8(ma, 22),
      _mm256_extract_epi8(ma, 21),
      _mm256_extract_epi8(ma, 20),
      _mm256_extract_epi8(ma, 19),
      _mm256_extract_epi8(ma, 18),
      _mm256_extract_epi8(ma, 17),
      _mm256_extract_epi8(ma, 16),
      _mm256_extract_epi8(ma, 15),
      _mm256_extract_epi8(ma, 14),
      _mm256_extract_epi8(ma, 13),
      _mm256_extract_epi8(ma, 12),
      _mm256_extract_epi8(ma, 11),
      _mm256_extract_epi8(ma, 10),
      _mm256_extract_epi8(ma, 9),
      _mm256_extract_epi8(ma, 8),
      _mm256_extract_epi8(ma, 7),
      _mm256_extract_epi8(ma, 6),
      _mm256_extract_epi8(ma, 5),
      _mm256_extract_epi8(ma, 4),
      _mm256_extract_epi8(ma, 3),
      _mm256_extract_epi8(ma, 2),
      _mm256_extract_epi8(ma, 1),
      _mm256_extract_epi8(ma, 0),
      name);
}

// sum all letters on word in each respective bytes
__m256i
break_chars_simd(const std::string& name)
{
    const char* ptr;
    // defining masks for all letters
    __m256i bits = _mm256_set_epi8(0x0,
                                   0x0,
                                   0x0,
                                   0x0,
                                   0x0,
                                   0x0,
                                   0x0,  // z
                                   0x0,  // y
                                   0x0,  // x
                                   0x0,  // w
                                   0x0,  // v
                                   0x0,  // u
                                   0x0,  // t
                                   0x0,  // s
                                   0x0,  // r
                                   0x0,  // q
                                   0x0,  // p
                                   0x0,  // o
                                   0x0,  // n
                                   0x0,  // m
                                   0x0,  // l
                                   0x0,  // k
                                   0x0,  // j
                                   0x0,  // i
                                   0x0,  // h
                                   0x0,  // g
                                   0x0,  // f
                                   0x0,  // e
                                   0x0,  // d
                                   0x0,  // c
                                   0x0,  // b
                                   0x0); // a
    __m256i ma = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x1); // a
    __m256i mb = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x1,  // b
                                 0x0); // a
    __m256i mc = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x1,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i md = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x1,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i me = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x1,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mf = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x1,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mg = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x1,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mh = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x1,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mi = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x1,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mj = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x1,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mk = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x1,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i ml = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x1,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mm = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x1,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mn = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x1,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mo = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x1,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mp = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x1,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mq = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x1,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mr = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x1,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i ms = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x1,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mt = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x1,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mu = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x1,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mv = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x1,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mw = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x1,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mx = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x0,  // y
                                 0x1,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i my = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,  // z
                                 0x1,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a
    __m256i mz = _mm256_set_epi8(0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x0,
                                 0x1,  // z
                                 0x0,  // y
                                 0x0,  // x
                                 0x0,  // w
                                 0x0,  // v
                                 0x0,  // u
                                 0x0,  // t
                                 0x0,  // s
                                 0x0,  // r
                                 0x0,  // q
                                 0x0,  // p
                                 0x0,  // o
                                 0x0,  // n
                                 0x0,  // m
                                 0x0,  // l
                                 0x0,  // k
                                 0x0,  // j
                                 0x0,  // i
                                 0x0,  // h
                                 0x0,  // g
                                 0x0,  // f
                                 0x0,  // e
                                 0x0,  // d
                                 0x0,  // c
                                 0x0,  // b
                                 0x0); // a

    ptr = name.c_str();
    while (ptr && *ptr) {
        switch (*ptr) {
            case 'a':
                bits = _mm256_add_epi8(bits, ma);
                break;
            case 'b':
                bits = _mm256_add_epi8(bits, mb);
                break;
            case 'c':
                bits = _mm256_add_epi8(bits, mc);
                break;
            case 'd':
                bits = _mm256_add_epi8(bits, md);
                break;
            case 'e':
                bits = _mm256_add_epi8(bits, me);
                break;
            case 'f':
                bits = _mm256_add_epi8(bits, mf);
                break;
            case 'g':
                bits = _mm256_add_epi8(bits, mg);
                break;
            case 'h':
                bits = _mm256_add_epi8(bits, mh);
                break;
            case 'i':
                bits = _mm256_add_epi8(bits, mi);
                break;
            case 'j':
                bits = _mm256_add_epi8(bits, mj);
                break;
            case 'k':
                bits = _mm256_add_epi8(bits, mk);
                break;
            case 'l':
                bits = _mm256_add_epi8(bits, ml);
                break;
            case 'm':
                bits = _mm256_add_epi8(bits, mm);
                break;
            case 'n':
                bits = _mm256_add_epi8(bits, mn);
                break;
            case 'o':
                bits = _mm256_add_epi8(bits, mo);
                break;
            case 'p':
                bits = _mm256_add_epi8(bits, mp);
                break;
            case 'q':
                bits = _mm256_add_epi8(bits, mq);
                break;
            case 'r':
                bits = _mm256_add_epi8(bits, mr);
                break;
            case 's':
                bits = _mm256_add_epi8(bits, ms);
                break;
            case 't':
                bits = _mm256_add_epi8(bits, mt);
                break;
            case 'u':
                bits = _mm256_add_epi8(bits, mu);
                break;
            case 'w':
                bits = _mm256_add_epi8(bits, mw);
                break;
            case 'v':
                bits = _mm256_add_epi8(bits, mv);
                break;
            case 'x':
                bits = _mm256_add_epi8(bits, mx);
                break;
            case 'y':
                bits = _mm256_add_epi8(bits, my);
                break;
            case 'z':
                bits = _mm256_add_epi8(bits, mz);
                break;
            default:
                std::cout << "invalid letter at word[" << name
                          << "]" << std::endl;
                exit(1);
        }
        ++ptr;
    }
#ifdef SHOW_DEBUG
    print_chars(name.c_str(), bits);
#endif
    return bits;
}
#else
unsigned int
break_chars(const std::string& name,
            int& a,
            int& b,
            int& c,
            int& d,
            int& e,
            int& f,
            int& g,
            int& h,
            int& i,
            int& j,
            int& k,
            int& l,
            int& m,
            int& n,
            int& o,
            int& p,
            int& q,
            int& r,
            int& s,
            int& t,
            int& u,
            int& v,
            int& w,
            int& x,
            int& y,
            int& z)
{
    unsigned int bits = 0x0;
    const char* ptr;
    ZERO_ABCDFG;
    ptr = name.c_str();
    while (ptr && *ptr) {
        switch (*ptr) {
            case 'a':
                ++a;
                break;
            case 'b':
                ++b;
                break;
            case 'c':
                ++c;
                break;
            case 'd':
                ++d;
                break;
            case 'e':
                ++e;
                break;
            case 'f':
                ++f;
                break;
            case 'g':
                ++g;
                break;
            case 'h':
                ++h;
                break;
            case 'i':
                ++i;
                break;
            case 'j':
                ++j;
                break;
            case 'k':
                ++k;
                break;
            case 'l':
                ++l;
                break;
            case 'm':
                ++m;
                break;
            case 'n':
                ++n;
                break;
            case 'o':
                ++o;
                break;
            case 'p':
                ++p;
                break;
            case 'q':
                ++q;
                break;
            case 'r':
                ++r;
                break;
            case 's':
                ++s;
                break;
            case 't':
                ++t;
                break;
            case 'u':
                ++u;
                break;
            case 'w':
                ++w;
                break;
            case 'v':
                ++v;
                break;
            case 'x':
                ++x;
                break;
            case 'y':
                ++y;
                break;
            case 'z':
                ++z;
                break;
            default:
                std::cout << "invalid letter at word[" << name
                          << "]" << std::endl;
                exit(1);
        }
        ++ptr;
    }
    SET_BIT(a)
    SET_BIT(b)
    SET_BIT(c)
    SET_BIT(d)
    SET_BIT(e)
    SET_BIT(f)
    SET_BIT(g)
    SET_BIT(h)
    SET_BIT(i)
    SET_BIT(j)
    SET_BIT(k)
    SET_BIT(l)
    SET_BIT(m)
    SET_BIT(n)
    SET_BIT(o)
    SET_BIT(p)
    SET_BIT(q)
    SET_BIT(r)
    SET_BIT(s)
    SET_BIT(t)
    SET_BIT(u)
    SET_BIT(v)
    SET_BIT(w)
    SET_BIT(x)
    SET_BIT(y)
    SET_BIT(z)
#ifdef SHOW_DEBUG
    std::bitset<26> bitset(bits);
    std::cout << "3  //" << name << "\n";
    std::cout << "3    " << bitset << std::endl;
#endif
    return bits;
}
void
insertBits(const char* word)
{
    unsigned int bits = 0x0;
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x,
      y, z;
    a = b = c = d = e = f = g = h = i = j = k = l = m = n = o = p = q = r = s =
      t = u = v = x = w = y = z = 0;
    bits = break_chars(word, ABCDEFG);
    // add bit set on map
    bitmap.push_back(bits);
}
#endif

void
generateDictionaryBits(const char* filename)
{
    std::ifstream in(filename);
    if (!in) // Always test the file open.
    {
        std::cout << "Cannot open dictionary file " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
#ifdef IGNORE_WORDS_WITH_LESS_LETTERS
        if (line.size() <= 2)
            continue;
#endif
        palavras.push_back(line);
#ifndef USE_SIMD
        insertBits(line.c_str());
#endif
    }
#ifdef USE_SIMD
    // store big array with bitmap!
    bitmap = reinterpret_cast<__m256i*>(
      _mm_malloc(palavras.size() * sizeof(__m256i), 64));
    __m256i* current = bitmap;
    for (auto entry : palavras) {
        *current = break_chars_simd(entry);
        ++current;
    }
#ifdef SHOW_DEBUG
    for (auto entry : palavras) {
        print_chars(entry.c_str(), break_chars_simd(entry));
    }
#endif
#endif
}
#ifdef USE_SIMD
void
consume_chars_simd(unsigned int index,
                   const std::string& output,
                   __m256i original,
                   __m256i consume)
{
    __m256i bits;
    // consume chars
    bits = _mm256_sub_epi8(original, consume);
#ifdef SHOW_DEBUG
    print_chars("orig ", original);
    print_chars("cons ", consume);
    print_chars("bits ", bits);
    std::cout << _mm256_movemask_epi8(bits) << std::endl;
#endif
    __m256i zero = _mm256_set_epi8(0x0,
                                   0x0,
                                   0x0,
                                   0x0,
                                   0x0,
                                   0x0,
                                   0x0,  // z
                                   0x0,  // y
                                   0x0,  // x
                                   0x0,  // w
                                   0x0,  // v
                                   0x0,  // u
                                   0x0,  // t
                                   0x0,  // s
                                   0x0,  // r
                                   0x0,  // q
                                   0x0,  // p
                                   0x0,  // o
                                   0x0,  // n
                                   0x0,  // m
                                   0x0,  // l
                                   0x0,  // k
                                   0x0,  // j
                                   0x0,  // i
                                   0x0,  // h
                                   0x0,  // g
                                   0x0,  // f
                                   0x0,  // e
                                   0x0,  // d
                                   0x0,  // c
                                   0x0,  // b
                                   0x0); // a
    __m256i meq = _mm256_cmpeq_epi8(bits, zero);
    if (_mm256_movemask_epi8(meq) == -1) {
        // found anagram!
        std::cout << output << std::endl;
        return;
    }
    // seek more words
    unsigned int total = palavras.size();
    for (unsigned int i = index; i < total; i++) {
        __m256i meq = _mm256_cmpeq_epi8(bits, bitmap[i]);
        __m256i mgt = _mm256_cmpgt_epi8(bits, bitmap[i]);
        __m256i mor = _mm256_or_si256(meq, mgt);
#ifdef SHOW_DEBUG
        print_chars("meq ", meq);
        print_chars("mgt ", mgt);
        print_chars("mor ", mor);
        std::cout << palavras[i] << " " << _mm256_movemask_epi8(mor)
                  << std::endl;
#endif
        if (_mm256_movemask_epi8(mor) == -1) {
            std::string loutput = output;
            loutput += palavras[i] + " ";
            consume_chars_simd(i, loutput, bits, bitmap[i]);
        }
    }
}
#else
void
consume_chars(unsigned int index,
              const std::string& output,
              ABCDEFG_DEC,
              _ABCDEFG_DEC)
{
    unsigned int bits = 0x0;
#ifdef SHOW_DEBUG
    std::cout << "consuming [" << palavras[index] << "]" << std::endl;
    std::cout << "          [" << output << "]" << std::endl;
#endif
    // consumes chars
    if (a >= _a) {
        a -= _a;
    } else {
        return;
    }
    if (b >= _b) {
        b -= _b;
    } else {
        return;
    }
    if (c >= _c) {
        c -= _c;
    } else {
        return;
    }
    if (d >= _d) {
        d -= _d;
    } else {
        return;
    }
    if (e >= _e) {
        e -= _e;
    } else {
        return;
    }
    if (f >= _f) {
        f -= _f;
    } else {
        return;
    }
    if (g >= _g) {
        g -= _g;
    } else {
        return;
    }
    if (h >= _h) {
        h -= _h;
    } else {
        return;
    }
    if (i >= _i) {
        i -= _i;
    } else {
        return;
    }
    if (j >= _j) {
        j -= _j;
    } else {
        return;
    }
    if (k >= _k) {
        k -= _k;
    } else {
        return;
    }
    if (l >= _l) {
        l -= _l;
    } else {
        return;
    }
    if (m >= _m) {
        m -= _m;
    } else {
        return;
    }
    if (n >= _n) {
        n -= _n;
    } else {
        return;
    }
    if (o >= _o) {
        o -= _o;
    } else {
        return;
    }
    if (p >= _p) {
        p -= _p;
    } else {
        return;
    }
    if (q >= _q) {
        q -= _q;
    } else {
        return;
    }
    if (r >= _r) {
        r -= _r;
    } else {
        return;
    }
    if (s >= _s) {
        s -= _s;
    } else {
        return;
    }
    if (t >= _t) {
        t -= _t;
    } else {
        return;
    }
    if (u >= _u) {
        u -= _u;
    } else {
        return;
    }
    if (v >= _v) {
        v -= _v;
    } else {
        return;
    }
    if (w >= _w) {
        w -= _w;
    } else {
        return;
    }
    if (x >= _x) {
        x -= _x;
    } else {
        return;
    }
    if (y >= _y) {
        y -= _y;
    } else {
        return;
    }
    if (z >= _z) {
        z -= _z;
    } else {
        return;
    }
    // check for ending
    if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0 && g == 0 &&
        h == 0 && i == 0 && j == 0 && k == 0 && l == 0 && m == 0 && n == 0 &&
        o == 0 && p == 0 && q == 0 && r == 0 && s == 0 && t == 0 && u == 0 &&
        v == 0 && w == 0 && x == 0 && y == 0 && z == 0) {
        // found anagram!
        std::cout << output << std::endl;
        return;
    }
    // creates new mask to compare
    SET_BIT(a)
    SET_BIT(b)
    SET_BIT(c)
    SET_BIT(d)
    SET_BIT(e)
    SET_BIT(f)
    SET_BIT(g)
    SET_BIT(h)
    SET_BIT(i)
    SET_BIT(j)
    SET_BIT(k)
    SET_BIT(l)
    SET_BIT(m)
    SET_BIT(n)
    SET_BIT(o)
    SET_BIT(p)
    SET_BIT(q)
    SET_BIT(r)
    SET_BIT(s)
    SET_BIT(t)
    SET_BIT(u)
    SET_BIT(v)
    SET_BIT(w)
    SET_BIT(x)
    SET_BIT(y)
    SET_BIT(z)
#ifdef SHOW_DEBUG
    std::bitset<26> bitsetName(bits);
    std::cout << "mask sub " << palavras[index] << " " << bitsetName
              << std::endl;
#endif
    // compares again
    unsigned int total = palavras.size();
    for (unsigned int subindex = index; subindex < total; subindex++) {
        if ((bitmap[subindex] & bits) == bitmap[subindex]) {
#ifdef SHOW_DEBUG
            std::cout << "2 match " << palavras[subindex] << std::endl;
            std::bitset<26> bitset(bitmap[subindex]);
            std::bitset<26> bitsetCalc(bitmap[subindex] & bits);
            std::cout << "2  //" << palavras[subindex] << "\n";
            std::cout << "2    " << bitset << std::endl;
            std::cout << "2    " << bitsetName << std::endl;
            std::cout << "2    " << bitsetCalc << std::endl;
#endif
            int _ABCDEFG;
            // remove bits and call again
            break_chars(palavras[subindex], _ABCDEFG);
            std::string loutput = output;
            loutput += palavras[subindex] + " ";
            consume_chars(subindex, loutput, ABCDEFG, _ABCDEFG);
        }
    }
}
#endif
#ifdef USE_SIMD
void
generateAnagramSimd(const char* name)
{
    __m256i bits = break_chars_simd(name);
#ifdef SHOW_DEBUG
    std::cout << "analising " << name << std::endl;
#endif
    unsigned int total = palavras.size();
    for (unsigned int i = 0; i < total; i++) {
        __m256i meq = _mm256_cmpeq_epi8(bits, bitmap[i]);
        __m256i mgt = _mm256_cmpgt_epi8(bits, bitmap[i]);
        __m256i mor = _mm256_or_si256(meq, mgt);
#ifdef SHOW_DEBUG
        print_chars("meq ", meq);
        print_chars("mgt ", mgt);
        print_chars("mor ", mor);
        std::cout << palavras[i] << " " << _mm256_movemask_epi8(mor)
                  << std::endl;
#endif
        if (_mm256_movemask_epi8(mor) == -1) {
            std::string output;
            output += palavras[i] + " ";
            consume_chars_simd(i, output, bits, bitmap[i]);
        }
    }
}
#else
void
generateAnagram(const char* name)
{
    unsigned int bits;
    int ABCDEFG;
#ifdef SHOW_DEBUG
    std::cout << "analising " << name << std::endl;
#endif
    bits = break_chars(name, ABCDEFG);
    unsigned int total = palavras.size();
    for (unsigned int subindex = 0; subindex < total; subindex++) {
        if ((bitmap[subindex] & bits) == bitmap[subindex]) {
#ifdef SHOW_DEBUG
            std::cout << "1 match " << palavras[subindex] << std::endl;
            std::bitset<26> bitset(bitmap[subindex]);
            std::bitset<26> bitsetName(bits);
            std::bitset<26> bitsetCalc(bitmap[subindex] & bits);
            std::cout << "1  //" << palavras[subindex] << "\n";
            std::cout << "1    " << bitset << std::endl;
            std::cout << "1  //" << name << "\n";
            std::cout << "1    " << bitsetName << std::endl;
            std::cout << "1    " << bitsetCalc << std::endl;
#endif
            // consumes word
            int _ABCDEFG;
            break_chars(palavras[subindex], _ABCDEFG);
            std::string output;
            output += palavras[subindex] + " ";
            consume_chars(subindex, output, ABCDEFG, _ABCDEFG);
        }
    }
}
#endif
int
main(int argc, const char** argv)
{
    if (argc > 1) {
        generateDictionaryBits(argv[1]);
#ifdef USE_SIMD
        generateAnagramSimd(argv[2]);
        if (bitmap) {
            _mm_free(bitmap);
        }
#else
        generateAnagram(argv[2]);
#endif
    }
    return 0;
}