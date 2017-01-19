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

    testParser::data_vector_t data = testParser::readFile(argv[1]);
    if (data.empty())
    {
        std::cout << "Empty test_file!" << std::endl;
        return -1;
    }

    testBench test;

    std::cout << "-----" << std::endl;

    // Do test
    unsigned char reg = 0x1c; // check ENV3 by default
    int cycle = 0;
    for (auto &d : data)
    {
        if (d[0] == testParser::cycle)
        {
            while (cycle != d[1])
            {
                test.clock();
                if (!test.compare(reg))
                    std::cout << "Fail!" << std::endl;
                cycle++;
#if DEBUG > 1
                std::cout << std::dec << "cycle " << cycle << std::endl;
#endif
            }
        }
        else if (d[0] == testParser::end)
        {
            break;
        }
        else if (d[0] == testParser::check)
        {
#ifdef DEBUG
            std::cout << std::hex << "Checking reg $" << (int)d[1] << std::endl;
#endif
            reg = d[1];
        }
        else
        {
#ifdef DEBUG
            std::cout << std::hex << "Writing $" << (int)d[1] << " to reg $" << (int)d[0] << std::endl;
#endif
            test.write(d[0], d[1]);
        }
    }
}
