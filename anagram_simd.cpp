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
#include "anagram.h"
std::vector<std::string> palavras;
std::list<std::string> listaPalavras;
__m256i* bitmap = nullptr;

void
print_chars(const char* name, __m256i ma)
{
    printf("m_ "
           "%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%."
           "2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x - "
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
break_chars(const std::string& name)
{
    const char* ptr;
    // defining masks for all letters
    __m256i bits = _mm256_set_epi8(0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0);
    __m256i ma = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1);
    __m256i mb = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0);
    __m256i mc = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0);
    __m256i md = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0);
    __m256i me = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mf = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mg = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mh = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mi = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mj = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mk = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i ml = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mm = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mn = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mo = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mp = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mq = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mr = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i ms = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mt = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mu = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mv = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mw = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mx = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i my = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);
    __m256i mz = _mm256_set_epi8(0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 1,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0);

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
                std::cout << "invalid letter at word[" << name << "]"
                          << std::endl;
                const char* letter = name.c_str();
                printf("<");
                while (*letter) {
                    printf("%x,", 0xff & *letter);
                    ++letter;
                }
                printf(">\n");
                exit(1);
        }
        ++ptr;
    }
#ifdef SHOW_DEBUG
    print_chars(name.c_str(), bits);
#endif
    return bits;
}

void
consume_chars(unsigned int index,
              std::string& output,
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
    __m256i zero = _mm256_set_epi8(0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0);
    __m256i meq = _mm256_cmpeq_epi8(bits, zero);
    if (_mm256_movemask_epi8(meq) == -1) {
        // found anagram!
        std::cout << output << std::endl;
        return;
    }
    // seek more words
    unsigned int total = palavras.size();

    for (unsigned int subindex = index; subindex < total; subindex++) {
        __m256i meq = _mm256_cmpeq_epi8(bits, bitmap[subindex]);
        __m256i mgt = _mm256_cmpgt_epi8(bits, bitmap[subindex]);
        __m256i mor = _mm256_or_si256(meq, mgt);
#ifdef SHOW_DEBUG
        print_chars("meq ", meq);
        print_chars("mgt ", mgt);
        print_chars("mor ", mor);
        std::cout << palavras[subindex] << " " << _mm256_movemask_epi8(mor)
                  << std::endl;
#endif
        if (_mm256_movemask_epi8(mor) == -1) {
            auto lastSize = output.size();
            output += palavras[subindex];
            output.push_back(' ');
            consume_chars(subindex, output, bits, bitmap[subindex]);
            output.resize(lastSize);
        }
    }
}

void
generateAnagramSimd(const char* name)
{
    __m256i bits = break_chars(name);
#ifdef SHOW_DEBUG
    std::cout << "analising " << name << std::endl;
#endif
    unsigned int total = palavras.size();
    std::string output;
    for (unsigned int index = 0; index < total; index++) {
        __m256i meq = _mm256_cmpeq_epi8(bits, bitmap[index]);
        __m256i mgt = _mm256_cmpgt_epi8(bits, bitmap[index]);
        __m256i mor = _mm256_or_si256(meq, mgt);
#ifdef SHOW_DEBUG
        print_chars("meq ", meq);
        print_chars("mgt ", mgt);
        print_chars("mor ", mor);
        std::cout << palavras[index] << " " << _mm256_movemask_epi8(mor)
                  << std::endl;
#endif

        if (_mm256_movemask_epi8(mor) == -1) {
            auto lastSize = output.size();
            output = palavras[index];
            output.push_back(' ');
            consume_chars(index, output, bits, bitmap[index]);
            output.resize(lastSize);
        }
    }
}

void
generateDictionaryBits(const char* filename, const char* targetString)
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
        // add word in list to process later
        listaPalavras.push_back(line);
    }
    // store big array with bitmap!
    bitmap = reinterpret_cast<__m256i*>(
      _mm_malloc(listaPalavras.size() * sizeof(__m256i), 64));
    __m256i* current = bitmap;
    __m256i bits;
    __m256i tmpBits = break_chars(targetString);
    __m256i fullBits = _mm256_set1_epi32(0xffffffff);
    __m256i targetBits =
      _mm256_cmpgt_epi8(fullBits, _mm256_andnot_si256(tmpBits, fullBits));
    for (auto entry : listaPalavras) {

        bits = break_chars(entry);
        __m256i mor = _mm256_or_si256(bits, targetBits);
        __m256i mgt = _mm256_cmpgt_epi8(mor, targetBits);
#ifdef SHOW_DEBUG
        print_chars("targetBits ", targetBits);
        print_chars("bits ", bits);
        print_chars("mor ", mor);
        print_chars("mgt ", mgt);
        std::cout << entry << " " << _mm256_movemask_epi8(mgt) << std::endl;
#endif
        if (_mm256_movemask_epi8(mgt) > 0) {
#ifdef SHOW_DEBUG
            std::cout << "cannot use word [" << entry
                      << "] - removing from dictionary" << std::endl;
#endif
            continue;
        } else {
            palavras.push_back(entry);
            *current = bits;
            ++current;
        }
    }
#ifdef SHOW_DEBUG
    for (auto entry : listaPalavras) {
        print_chars(entry.c_str(), break_chars(entry));
    }
#endif
}
void
freeBitmap()
{
    if (bitmap) {
        _mm_free(bitmap);
    }
}
