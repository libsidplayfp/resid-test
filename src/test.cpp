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

#include "residfpWrapper.h"
#include "residWrapper.h"

#include <iostream>
#include <memory>

void usage(const char* prog)
{
    std::cout << "Usage " << prog << " --engine=[resid|residfp] <test_file>" << std::endl;
}

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        usage(argv[0]);
        return -1;
    }

    const std::string param(argv[1]);

    size_t pos = param.find_first_of("=");
    if (param.substr(0, pos).compare("--engine"))
    {
        usage(argv[0]);
        return -1;
    }

    const std::string file(argv[2]);

#ifdef DEBUG
    std::cout << "Reading file: " << file << std::endl;
#endif

    testBench::data_vector_t data = testParser::readFile(file);
    if (data.empty())
    {
        std::cout << "Empty test_file!" << std::endl;
        return -2;
    }

    std::unique_ptr<wrapper> sidWrapper;
    std::string engine = param.substr(pos+1);
    if (engine.compare("residfp") == 0)
    {
        sidWrapper.reset(new residfpWrapper());
    }
    else if (engine.compare("resid") == 0)
    {
        sidWrapper.reset(new residWrapper());
    }
    else
    {
        usage(argv[0]);
        return -1;
    }

    std::cout << "Testing " << engine << " engine" << std::endl;

    testBench test(sidWrapper.get());
#ifdef DEBUG
    std::cout << "-----" << std::endl;
#endif

    if (!test.execute(data))
        return -10;
}
