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
#include "testParser.h"

#include <iostream>

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage " << argv[0] << " <test_file>" << std::endl;
        return -1;
    }

#ifdef DEBUG
    std::cout << "Reading file: " << argv[1] << std::endl;
#endif

    testBench::data_vector_t data = testParser::readFile(argv[1]);
    if (data.empty())
    {
        std::cout << "Empty test_file!" << std::endl;
        return -2;
    }

    testBench test;
#ifdef DEBUG
    std::cout << "-----" << std::endl;
#endif
    if (!test.execute(data))
        return -10;
}
