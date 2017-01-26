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
 
#include "residfpWrapper.h"

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "residfp/SID.h"

residfpWrapper::residfpWrapper()
{
    sid = new reSIDfp::SID();
#ifdef ENABLE_MOS8580
    sid->setChipModel(reSIDfp::MOS8580);
#else
    sid->setChipModel(reSIDfp::MOS6581);
#endif
}

residfpWrapper::~residfpWrapper()
{
    delete sid;
}

void residfpWrapper::clock()
{
    sid->clockSilent(1);
}

unsigned char residfpWrapper::read(unsigned char addr) 
{
    sid->clockSilent(1);
    return sid->read(addr);
}

void residfpWrapper::write(unsigned char addr, unsigned char data) 
{
    sid->clockSilent(1);
    sid->write(addr, data);
}
