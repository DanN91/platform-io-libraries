/*
    NokiaDisplay: wrapper over Nokia 5110 display ( 5x8 font, CHIP PCD8544 ) providing basic functionality.
    Adapted after PCD8544 library, Copyright (c) 2010 Carlos Rodrigues
    Author: Daniel Nistor
    MIT License, 2021
*/
#pragma once

#include <Arduino.h>

class NokiaDisplay final
{
public:
    // One instance
    static NokiaDisplay& getInstance(uint8_t reset, uint8_t chipEnable, uint8_t dataSelect, uint8_t dataIn, uint8_t clock);

    // 84 x 48 dimension
    void Initialize();

    // Erase everything on the display...
    void Clear();
    void ClearLine();  // ...or just the current line

    // Set display contrast level (0-127)...
    void SetContrast(uint8_t level);

    // Place the cursor at position...
    void SetCursor(uint8_t line, uint8_t column);

    // Write various types
    void Write(const char* text);
    void Write(String&& text);
    void Write(String& text);
    void Write(uint32_t number);

    enum class Aligned : uint8_t
    {
        Left = 0,
        Center,
        Right
    };

    void Write(uint8_t line, const char* text, Aligned aligned);
    void Write(uint8_t line, uint32_t number, Aligned aligned);

private:
	NokiaDisplay(uint8_t reset, uint8_t chipEnable, uint8_t dataSelect, uint8_t dataIn, uint8_t clock);

	// singleton
    NokiaDisplay(const NokiaDisplay&) = delete;
    NokiaDisplay& operator=(const NokiaDisplay&) = delete;
    NokiaDisplay(NokiaDisplay&&) = delete;
    NokiaDisplay& operator=(NokiaDisplay&&) = delete;

    enum class OpType : uint8_t
    {
        CMD = 0,
        DATA = 1
    };

    // Write ASCII char and update the cursor
    void WriteChar(uint8_t character);
    void WriteDigit(uint8_t digit);

    uint8_t SizeInPixels(const char* text) const;
    uint8_t SizeInPixels(uint32_t number) const;

    uint8_t ColumnPixelPosition(uint8_t sizeInPixels, Aligned aligned) const;

    // Send a command or data to the display...
    void Send(OpType type, uint8_t data);
    void UpdateCursor();

    const uint8_t m_reset;
	const uint8_t m_sce;
    const uint8_t m_dc;
    const uint8_t m_sdin;
    const uint8_t m_sclk;

    // Current cursor position...
    uint8_t m_column = 0;
    uint8_t m_line   = 0;

	bool m_isCursorValid = false;
};