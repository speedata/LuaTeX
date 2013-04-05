/* pdflua.c

   Copyright 2010 Taco Hoekwater <taco@luatex.org>
   Copyright 2010 Hartmut Henkel <hartmut@luatex.org>

   This file is part of LuaTeX.

   LuaTeX is free software; you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2 of the License, or (at your
   option) any later version.

   LuaTeX is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.

   You should have received a copy of the GNU General Public License along
   with LuaTeX; if not, see <http://www.gnu.org/licenses/>. */

#include "ptexlib.h"

static const Byte compr[258] = {
    0x78, 0x9c, 0xad, 0x51, 0xc1, 0x4a, 0xc4, 0x30, 0x10, 0xbd, 0xe7, 0x2b, 0xe6, 0xd0, 0x83, 0xc2,
    0x36, 0x49, 0x77, 0x05, 0x69, 0x61, 0x3f, 0x40, 0xf0, 0x24, 0x78, 0xf1, 0x96, 0xa6, 0xd3, 0x36,
    0x34, 0x24, 0x61, 0x92, 0xb8, 0x2e, 0xe2, 0xbf, 0x9b, 0x42, 0xd1, 0x55, 0xf1, 0xb6, 0x61, 0x12,
    0x1e, 0xf3, 0xde, 0xcc, 0x7b, 0x90, 0xba, 0x86, 0xea, 0x61, 0xe8, 0x20, 0x0c, 0xa3, 0xcd, 0x8a,
    0x97, 0x0b, 0x87, 0xf6, 0xae, 0x85, 0xbd, 0x6c, 0x64, 0xdd, 0x34, 0xb5, 0xbc, 0x07, 0x29, 0x3b,
    0xd9, 0x76, 0x4d, 0xfb, 0x02, 0xf3, 0x8c, 0x6e, 0x41, 0x0b, 0x15, 0xab, 0xcb, 0xd8, 0xf3, 0xd3,
    0x63, 0x07, 0x73, 0x4a, 0x21, 0x76, 0x42, 0x8c, 0x3e, 0xbb, 0x81, 0xce, 0x3c, 0xe6, 0x80, 0x16,
    0x35, 0x1f, 0x49, 0xc4, 0x57, 0x27, 0xca, 0xbe, 0x84, 0x6f, 0xa2, 0x27, 0xe5, 0xf4, 0x8c, 0x51,
    0x24, 0x5b, 0x16, 0x1f, 0x44, 0xf4, 0x99, 0x34, 0x8a, 0x42, 0x2d, 0xe2, 0x84, 0xfd, 0x5e, 0x6f,
    0xc2, 0xc1, 0xd0, 0x8a, 0xa2, 0x26, 0x13, 0x52, 0x14, 0x17, 0xa1, 0x2a, 0xb6, 0x7a, 0xa6, 0xd9,
    0x44, 0x28, 0x85, 0x8a, 0xec, 0x19, 0x4e, 0x9e, 0x16, 0x30, 0x0e, 0x02, 0xf9, 0x89, 0x30, 0x46,
    0xce, 0xf9, 0xaa, 0xba, 0xce, 0x61, 0xac, 0xc7, 0xc9, 0xb8, 0xa0, 0x26, 0x84, 0x23, 0x8c, 0xd9,
    0xe9, 0x64, 0xbc, 0xbb, 0x51, 0xb7, 0x0c, 0xdd, 0xc0, 0xd6, 0xe7, 0x3f, 0xca, 0xe7, 0x14, 0x4a,
    0x15, 0x36, 0x26, 0xc2, 0x1f, 0x92, 0x4d, 0x71, 0xbd, 0x8c, 0xd6, 0x6b, 0x65, 0xb7, 0xcf, 0x2b,
    0x46, 0xef, 0x0c, 0xe0, 0x32, 0xf6, 0x17, 0xde, 0x15, 0xe2, 0x3b, 0xf2, 0x86, 0xd6, 0xe6, 0xdf,
    0xb0, 0xbf, 0x3a, 0x3b, 0xf6, 0xc1, 0x18, 0x61, 0xca, 0xe4, 0x36, 0x1f, 0xf6, 0x09, 0xc1, 0xee,
    0xa3, 0x68
};

static const zlib_struct compr_struct = { 564, 258, compr };

const zlib_struct *pdflua_zlib_struct_ptr = &compr_struct;
