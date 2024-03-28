/*
 * AT24C32.h
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

#pragma once

#include <Arduino.h>
#include <IStorage.h>

class AT24C32 final : public IStorage
{
public:
    AT24C32();
    virtual ~AT24C32() = default;

    void Initialize();

private:
    bool writeBytes(uint16_t address, uint8_t& data, uint8_t dataSize) override;
    bool readBytes(uint16_t address, uint8_t& data, uint8_t dataSize) override;
    bool clearBytes(uint16_t address, uint16_t count) override;

    void readImpl(uint16_t address, uint8_t *data, int n);
    void readImpl(uint16_t address, uint8_t *data, int offset, int n);

    void writeImpl(uint16_t address, uint8_t *data, int n);
    void writeImpl(uint16_t address, uint8_t *data, int offset, int n);

    const uint8_t m_address = 0x57;
    const uint8_t m_pageSize = 32;
};