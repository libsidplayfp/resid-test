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

#include "testParser.h"
 
#include <fstream>
#include <sstream>

namespace testParser
{

/*
 * Split a file into lines.
 */
std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    std::istringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        size_t end = item.find_last_not_of(" \n\r\t");
        if (end != std::string::npos)
            item.erase(end+1);
        elems.push_back(item);
    }
    return elems;
}

/**
 * Read test file.
 */
testBench::data_vector_t readFile(std::string fileName)
{
    std::ifstream ifs(fileName.c_str(), std::ifstream::in);
    std::string line;
    testBench::data_vector_t result;
    while (getline(ifs, line).good())
    {
        std::vector<std::string> values = split(line, ',');
        // skip comments and empty lines
        if (values.empty() || values[0][0] == '#')
        {
            continue;
        }

        testBench::data_t newVales;
        if (values[0].compare("cycle") == 0)
        {
            newVales.operation = testBench::tag::cycle;
            newVales.param1 = std::stoul(values[1]);
        }
        else if (values[0].compare("end") == 0)
        {
            newVales.operation = testBench::tag::end;
        }
        else if (values[0].compare("check") == 0)
        {
            if (values.size() != 1)
                continue;

            newVales.operation = testBench::tag::check;
            // TODO validate: only read regs allowed
            newVales.param1 = std::stoul(values[1], nullptr, 16);
        }
        else
        {
            if (values.size() != 2)
                continue;

            newVales.operation = testBench::tag::write;
            // TODO validate: check range
            newVales.param1 = std::stoul(values[0], nullptr, 16);
            newVales.param2 = std::stoul(values[1], nullptr, 16);
        }
        result.push_back(newVales);
    }
    return result;
}

}
