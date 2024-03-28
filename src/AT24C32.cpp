/*
 * AT24C32.cpp
 * Library for using the EEPROM AT24C32/64
 *
 * Copyright (c) 2014 Christian Paul
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * ADAPTATIONS TO CURRENT STATE MADE BY Daniel Nistor, 2024
 */

#include "AT24C32.h"

#include <Wire.h>

AT24C32::AT24C32()
    : IStorage(4096)
{
}

void AT24C32::Initialize()
{
    Wire.begin();
}

bool AT24C32::writeBytes(uint16_t address, uint8_t& data, uint8_t dataSize)
{
    writeImpl(address, &data, dataSize);
    return true;
}

bool AT24C32::readBytes(uint16_t address, uint8_t& data, uint8_t dataSize)
{
    readImpl(address, &data, dataSize);
    return true;
}

bool AT24C32::clearBytes(uint16_t address, uint16_t count)
{
    uint64_t zero = 0;
    uint8_t bytesLeft = count;
    uint8_t cursor = 0;

    while (bytesLeft > 0)
    {
        const uint8_t bytesWritten = min(sizeof(zero), bytesLeft);
        writeBytes(address + cursor, reinterpret_cast<uint8_t&>(zero), bytesWritten);
        bytesLeft -= bytesWritten;
        cursor += bytesWritten;
    }
}

void AT24C32::writeImpl(uint16_t address, uint8_t *data, int n)
{
    // status quo
    int c = n;    // uint8_ts left to write
    int offD = 0; // current offset in data pointer
    int offP;     // current offset in page
    int nc = 0;   // next n uint8_ts to write

    // write alle uint8_ts in multiple steps
    while (c > 0)
    {
        // calc offset in page
        offP = address % m_pageSize;
        // maximal 30 uint8_ts to write
        nc = min(min(c, 30), m_pageSize - offP);
        writeImpl(address, data, offD, nc);
        c -= nc;
        offD += nc;
        address += nc;
    }
}

void AT24C32::writeImpl(uint16_t address, uint8_t *data, int offset, int n)
{
    Wire.beginTransmission(m_address);

    if (Wire.endTransmission() == 0)
    {
        Wire.beginTransmission(m_address);

        Wire.write(address >> 8);
        Wire.write(address & 0xFF);

        uint8_t *adr = data + offset;
        Wire.write(adr, n);

        Wire.endTransmission();

        delay(20);
    }
}

void AT24C32::readImpl(uint16_t address, uint8_t *data, int n)
{
    int c = n;
    int offset = 0;

    while (c > 0) // read until are n uint8_ts read
    {
        const uint8_t nc = min(c, 32); // read maximal 32 uint8_ts
        readImpl(address, data, offset, nc);

        address += nc;
        offset += nc;

        c -= nc;
    }
}

void AT24C32::readImpl(uint16_t address, uint8_t *data, int offset, int n)
{
    Wire.beginTransmission(m_address);
    if (Wire.endTransmission() == 0)
    {
        Wire.beginTransmission(m_address);
        Wire.write(address >> 8);
        Wire.write(address & 0xFF);
        if (Wire.endTransmission() == 0)
        {
            int r = 0;
            Wire.requestFrom(m_address, n);
            while (Wire.available() > 0 && r < n)
            {
                data[offset + r] = (uint8_t)Wire.read();
                r++;
            }
        }
    }
}
