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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "resid/sid.h"

extern "C" {
#include "perfect6581/perfect6581.h"
}

#define DEBUG

typedef std::vector< std::vector<int> > ref_vector_t;

/******************************************/

void writeReg(void *state, unsigned char addr, unsigned char data)
{
    step(state); // Phi2 low

    setCs(state, 0);
    setRw(state, 0);
    writeAddress(state, addr);
    writeData(state, data);

    step(state); // Phi2 high
    setCs(state, 1);
}

unsigned char readReg(void *state, unsigned char addr)
{
    step(state); // Phi2 low

    setCs(state, 0);
    setRw(state, 1);
    writeAddress(state, addr);

    step(state); // Phi2 high
    unsigned char data = readData(state);

    setCs(state, 1);
    return data;
}

/******************************************/

bool compare(reSID::SID* sid, void *state, unsigned char addr)
{
    sid->clock();
    unsigned int a = sid->read(addr);
    unsigned int b = readReg(state, addr);
#ifdef DEBUG
    std::cout << std::hex << a << " - " << b << std::endl;
#endif
    return a == b;
}

void clock(reSID::SID* sid, void *state)
{
    sid->clock();
    step(state);
    step(state);
}

void write(reSID::SID* sid, void *state, unsigned char addr, unsigned char data)
{
    sid->write(addr, data);
    sid->clock();
    writeReg(state, addr, data);
}

/******************************************/

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
        elems.push_back(item);
    }
    return elems;
}

ref_vector_t readFile(std::string fileName)
{
#ifdef DEBUG
    std::cout << "Reading file: " << fileName << std::endl;
#endif
    std::ifstream ifs(fileName.c_str(), std::ifstream::in);
    std::string line;
    ref_vector_t result;
    while (getline(ifs, line).good())
    {
        std::vector<std::string> values = split(line, ',');
        std::vector<int> newVales;
        if (values[0].compare("cycle") == 0)
        {
            newVales.push_back(-1);
            newVales.push_back(std::stoul(values[1]));
        }
        else if (values[0].compare("end") == 0)
        {
            newVales.push_back(-10);
        }
        else
        {
            for (auto &val : values)
            {
                newVales.push_back(std::stoul(val, nullptr, 16));
            }
        }
        result.push_back(newVales);
    }
    return result;
}

/******************************************/

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage " << argv[0] << " <test_file>" << std::endl;
        return -1;
    }

    ref_vector_t data = readFile(argv[1]);

    reSID::SID* sid = new reSID::SID();
    void *state = initAndResetChip();
#ifdef DEBUG
    compare(sid, state, 0x1c);
#endif
    for (;;)
    {
        sid->clock();
        unsigned char a = sid->read(0x1C);
        if (a == 0x00)
            break;
    }

    for (;;)
    {
        unsigned char a = readReg(state, 0x1C);
        if (a == 0x00)
            break;
    }

    std::cout << "-----" << std::endl;

    // Do test
    int cycle = 0;
    for (auto &d : data)
    {
        if (d[0] == -1)
        {
            while (cycle != d[1])
            {
                clock(sid, state);
                bool res = compare(sid, state, 0x1c);
                if (!res)
                    std::cout << "Fail!" << std::endl;
                cycle++;
#ifdef DEBUG
        std::cout << std::dec << "cycle " << cycle << std::endl;
#endif
            }
        }
        else if (d[0] == -10)
        {
            break;
        }
        else
        {
#ifdef DEBUG
        std::cout << std::hex << "Writing " << (int)d[1] << " to reg " << (int)d[0] << std::endl;
#endif
            write(sid, state, d[0], d[1]);
        }
    }

    delete sid;
}
