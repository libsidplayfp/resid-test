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
 
#include "residWrapper.h"

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "resid/sid.h"

residWrapper::residWrapper()
{
    sid = new reSID::SID();
#ifdef ENABLE_MOS8580
    sid->set_chip_model(reSID::MOS8580);
#endif
}

residWrapper::~residWrapper()
{
    delete sid;
}

void residWrapper::clock()
{
    sid->clock();
}

unsigned char residWrapper::read(unsigned char addr) 
{
    sid->clock();
    return sid->read(addr);
}

void residWrapper::write(unsigned char addr, unsigned char data) 
{
    sid->clock();
    sid->write(addr, data);
}
