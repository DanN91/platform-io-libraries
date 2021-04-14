// Nokia Display CHIP PCD8544
// 5 x 8 font
// Modified from PCD8544 library, Copyright (c) 2010 Carlos Rodrigues
#pragma once

#include <Arduino.h>

class NokiaDisplay final
{
public:
    // One instance
    static NokiaDisplay& getInstance(byte reset = 6, byte chipEnable = 5, byte dataSelect = 4, byte dataIn = 3, byte clock = 2);

    // 84 x 48 dimension
    void initialize();

    // Erase everything on the display...
    void clear();
    void clearLine();  // ...or just the current line

    // Set display contrast level (0-127)...
    void setContrast(byte level);

    // Place the cursor at position...
    void setCursor(byte line, byte column);

    // Write text
    void writeText(const char* text);

    void writeText(String&& text);
    void writeText(String& text);

private:
	NokiaDisplay(byte reset, byte chipEnable, byte dataSelect, byte dataIn, byte clock);

	// singleton
    NokiaDisplay(const NokiaDisplay&) = delete;
    NokiaDisplay& operator=(const NokiaDisplay&) = delete;
    NokiaDisplay(NokiaDisplay&&) = delete;
    NokiaDisplay& operator=(NokiaDisplay&&) = delete;

    enum class OpType : byte
    {
        CMD = 0,
        DATA = 1
    };

    // Write ASCII char and update the cursor
    void writeChar(byte character);

    // Send a command or data to the display...
    void send(OpType type, byte data);

    const byte m_reset;
	const byte m_sce;
    const byte m_dc;
    const byte m_sdin;
    const byte m_sclk;

    // Current cursor position...
    byte m_column = 0;
    byte m_line   = 0;

	bool m_isCursorValid = false;
};