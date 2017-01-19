/*
 * Copyright 2016-2017 Leandro Nini
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "testBench.h"

#ifdef DEBUG
#  include <iostream>
#endif

testBench::testBench()
{
#ifdef DEBUG
    compare(0x1b);
    compare(0x1c);
#endif

    // stabilize envelope generator
    for (;;)
    {
        unsigned char const a = sid.read(0x1C);
        if (a == 0x00)
            break;
    }
    for (;;)
    {
        unsigned char const b = perfect6581.read(0x1C);
        if (b == 0x00)
            break;
    }
}

void testBench::clock()
{
    sid.clock();
    perfect6581.clock();
}

void testBench::write(unsigned char addr, unsigned char data)
{
    sid.write(addr, data);
    perfect6581.write(addr, data);
}

bool testBench::compare(unsigned char addr)
{
    unsigned int const a = sid.read(addr);

    unsigned int const b = perfect6581.read(addr);

#ifdef DEBUG
    std::cout << std::hex << a << " - " << b << std::endl;
#endif
    return a == b;
}
