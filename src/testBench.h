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
 
#ifndef TESTBENCH_H
#define TESTBENCH_H

#include "wrapper.h"
#include "perfect6581Wrapper.h"

#include <vector>

class testBench
{
public:
    enum class tag
    {
        write,
        check,
        run,
        end       
    };

    typedef struct
    {
        tag operation;
        int param1;
        int param2;
    } data_t;
    typedef std::vector<data_t> data_vector_t;

private:
    wrapper *sid;
    perfect6581Wrapper perfect6581;

private:
    void clock();
    void write(unsigned char addr, unsigned char data);
    bool compare(unsigned char addr);

public:
    testBench(wrapper *sid);

    bool execute(data_vector_t data);
};

#endif
