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
#ifdef USE_PARALLEL
#include "taskflow/taskflow.hpp"
#endif

std::vector<std::string> palavras;
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
unsigned int
break_chars(const std::string& name, ABCDEFG_DEC_REF)
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
bool
insertBits(const char* word, int targetBits)
{
    unsigned int bits = 0x0;
    int ABCDEFG;
    ZERO_ABCDFG;
    bits = break_chars(word, ABCDEFG);

    // check if it's a word impossible to match
    if (bits & (~targetBits)) {
#ifdef SHOW_DEBUG
        std::cout << "cannot use word [" << word
                  << "] - removing from dictionary" << std::endl;
#endif
        return false;
    } else {
        // add bit set on map
        bitmap.push_back(bits);
        return true;
    }
}

void
consume_chars(unsigned int index,
              std::string& output,
              ABCDEFG_DEC,
              _ABCDEFG_DEC)
{
    unsigned int bits = 0x0;
#ifdef SHOW_DEBUG
    std::cout << "consuming [" << palavras[index] << "]" << std::endl;
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
        // std::cout << output << std::endl;
        fprintf(stdout, "%s\n", output.c_str());
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
            auto lastSize = output.size();
            output += palavras[subindex];
            output.push_back(' ');
            consume_chars(subindex, output, ABCDEFG, _ABCDEFG);
            output.resize(lastSize);
        }
    }
}
#ifdef USE_PARALLEL
void
runner(const char* name,
       unsigned int total,
       unsigned int start,
       unsigned int step)
{
    unsigned int bits;
    int ABCDEFG;
    bits = break_chars(name, ABCDEFG);
    std::string output;
    for (unsigned int index = start; index < total; index += step) {
        if ((bitmap[index] & bits) == bitmap[index]) {
#ifdef SHOW_DEBUG
            std::cout << "1 match " << palavras[index] << std::endl;
            std::bitset<26> bitset(bitmap[index]);
            std::bitset<26> bitsetName(bits);
            std::bitset<26> bitsetCalc(bitmap[index] & bits);
            std::cout << "1  //" << palavras[index] << "\n";
            std::cout << "1    " << bitset << std::endl;
            std::cout << "1  //" << name << "\n";
            std::cout << "1    " << bitsetName << std::endl;
            std::cout << "1    " << bitsetCalc << std::endl;
#endif
            // consumes word
            int _ABCDEFG;
            auto lastSize = output.size();
            break_chars(palavras[index], _ABCDEFG);
            output = palavras[index];
            output.push_back(' ');
            consume_chars(index, output, ABCDEFG, _ABCDEFG);
            output.resize(lastSize);
        }
    }
}
void
generateAnagramParallel(const char* name)
{

#ifdef SHOW_DEBUG
    std::cout << "analising " << name << std::endl;
#endif
    unsigned int total = palavras.size();
    tf::Executor executor;
    tf::Taskflow taskflow;
    // 8 cpus
    unsigned int step = 8;
    taskflow.emplace([&]() { runner(name, total, 0, step); }).name("A1");
    taskflow.emplace([&]() { runner(name, total, 1, step); }).name("A2");
    taskflow.emplace([&]() { runner(name, total, 2, step); }).name("A3");
    taskflow.emplace([&]() { runner(name, total, 3, step); }).name("A4");
    taskflow.emplace([&]() { runner(name, total, 4, step); }).name("A5");
    taskflow.emplace([&]() { runner(name, total, 5, step); }).name("A6");
    taskflow.emplace([&]() { runner(name, total, 6, step); }).name("A7");
    taskflow.emplace([&]() { runner(name, total, 7, step); }).name("A8");
    executor.run(taskflow).wait();
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
    std::string output;
    for (unsigned int index = 0; index < total; index++) {
        if ((bitmap[index] & bits) == bitmap[index]) {
#ifdef SHOW_DEBUG
            std::cout << "1 match " << palavras[index] << std::endl;
            std::bitset<26> bitset(bitmap[index]);
            std::bitset<26> bitsetName(bits);
            std::bitset<26> bitsetCalc(bitmap[index] & bits);
            std::cout << "1  //" << palavras[index] << "\n";
            std::cout << "1    " << bitset << std::endl;
            std::cout << "1  //" << name << "\n";
            std::cout << "1    " << bitsetName << std::endl;
            std::cout << "1    " << bitsetCalc << std::endl;
#endif
            // consumes word
            int _ABCDEFG;
            auto lastSize = output.size();
            break_chars(palavras[index], _ABCDEFG);
            output = palavras[index];
            output.push_back(' ');
            consume_chars(index, output, ABCDEFG, _ABCDEFG);
            output.resize(lastSize);
        }
    }
}
#endif
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

    int ABCDEFG;
    int targetBits;
    targetBits = break_chars(targetString, ABCDEFG);
    bool canInsert;
    while (std::getline(in, line)) {
#ifdef IGNORE_WORDS_WITH_LESS_LETTERS
        if (line.size() <= 2)
            continue;
#endif
        canInsert = insertBits(line.c_str(), targetBits);
        if (canInsert) {
            palavras.push_back(line);
        }
    }
}
