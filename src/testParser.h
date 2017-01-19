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

#ifndef TESTPARSER_H
#define TESTPARSER_H

#include <string>
#include <vector>

namespace testParser
{
    enum tags
    {
        check = -10,
        cycle = -20,
        end   = -30,        
    };

    typedef std::vector<int> data_t;
    typedef std::vector<data_t> data_vector_t;

    data_vector_t readFile(std::string fileName);
};

#endif