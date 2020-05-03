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

#ifndef __MACROS_H_
#define __MACROS_H_

#define ZERO_ABCDFG                                                            \
    a = b = c = d = e = f = g = h = i = j = k = l = m = n = o = p = q = r =    \
      s = t = u = v = x = w = y = z = 0

#define ZERO_ABCDFG_                                                           \
    _a = _b = _c = _d = _e = _f = _g = _h = _i = _j = _k = _l = _m = _n = _o = \
      _p = _q = _r = _s = _t = _u = _v = _x = _w = _y = _z = 0

#define ABCDEFG                                                                \
    a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z

#define _ABCDEFG                                                               \
    _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p, _q, _r,    \
      _s, _t, _u, _v, _w, _x, _y, _z

#define COPY_ABCDEFG                                                           \
    int a = a, b = b, c = c, d = d, e = e, f = f, g = g, h = h, i = i, j = j,  \
        k = k, l = l, m = m, n = n, o = o, p = p, q = q, r = r, s = s, t = t,  \
        u = u, v = v, w = w, x = x, y = y, z = z

#define ABCDEFG_DEC_REF                                                        \
    int &a, int &b, int &c, int &d, int &e, int &f, int &g, int &h, int &i,    \
      int &j, int &k, int &l, int &m, int &n, int &o, int &p, int &q, int &r,  \
      int &s, int &t, int &u, int &v, int &w, int &x, int &y, int &z

#define _ABCDEFG_DEC_REF                                                       \
    int &_a, int &_b, int &_c, int &_d, int &_e, int &_f, int &_g, int &_h,    \
      int &_i, int &_j, int &_k, int &_l, int &_m, int &_n, int &_o, int &_p,  \
      int &_q, int &_r, int &_s, int &_t, int &_u, int &_v, int &_w, int &_x,  \
      int &_y, int &_z

#define ABCDEFG_DEC                                                            \
    int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,      \
      int k, int l, int m, int n, int o, int p, int q, int r, int s, int t,    \
      int u, int v, int w, int x, int y, int z

#define _ABCDEFG_DEC                                                           \
    int _a, int _b, int _c, int _d, int _e, int _f, int _g, int _h, int _i,    \
      int _j, int _k, int _l, int _m, int _n, int _o, int _p, int _q, int _r,  \
      int _s, int _t, int _u, int _v, int _w, int _x, int _y, int _z

#define SET_BIT(X)                                                             \
    if (X > 0) {                                                               \
        bits ^= 1UL << CharBits::X;                                            \
    }
#define CHK_BIT(X)                                                             \
    if ((bits >> CharBits::X) & 1U) {                                          \
        std::cout << #X << " is set " << CharBits::X << std::endl;             \
    }

#endif
