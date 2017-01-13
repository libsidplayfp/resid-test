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

#include "resid/sid.h"

extern "C" {
#include "perfect6581/perfect6581.h"
}

#define DEBUG

void
writeReg(void *state, unsigned char addr, unsigned char data)
{
    step(state); // Phi2 low

    setCs(state, 0);
    setRw(state, 0);
    writeAddress(state, addr);
    writeData(state, data);

    step(state); // Phi2 high
    setCs(state, 1);
}

unsigned char
readReg(void *state, unsigned char addr)
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

bool compare(reSID::SID* sid, void *state, unsigned char addr) {
    sid->clock();
    unsigned int a = sid->read(addr);
    unsigned int b = readReg(state, addr);
#ifdef DEBUG
    std::cout << std::hex << a << " - " << b << std::endl;
#endif
    return a == b;
}

void clock(reSID::SID* sid, void *state) {
    sid->clock();
    step(state);
    step(state);
}

void write(reSID::SID* sid, void *state, unsigned char addr, unsigned char data) {
    sid->write(addr, data);
    sid->clock();
    writeReg(state, addr, data);
}

int main () {

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

    std::cout << "-----!" << std::endl;

    // Do test
    write(sid, state, 0x13, 0x33);
    write(sid, state, 0x12, 0x01);

    for (int i=0; i<50000; i++) {
        clock(sid, state);
        bool res = compare(sid, state, 0x1c);
        if (!res)
            std::cout << "Fail!" << std::endl;
    }

    delete sid;
}
