/*
    NokiaDisplay: wrapper over Nokia 5110 display ( 5x8 font, CHIP PCD8544 ) providing basic functionality.
    Adapted after PCD8544 library, Copyright (c) 2010 Carlos Rodrigues
    Author: Daniel Nistor
    MIT License, 2021
*/
#include "NokiaDisplay.h"
#include "font.h"

namespace
{
    constexpr uint8_t WIDTH = 84;
    constexpr uint8_t HEIGHT = 48;
	constexpr uint8_t MAX_LINES_COUNT = 6;

    uint8_t GetDigitsCount(uint32_t number)
    {
        if (number == 0)
            return 1; // 0 is a digit

        uint8_t nrOfDigits = 0;
        while (number > 0)
        {
            number /= 10;
            nrOfDigits++;
        }

        return nrOfDigits;
    }
}

NokiaDisplay::NokiaDisplay(uint8_t reset, uint8_t chipEnable, uint8_t dataSelect, uint8_t dataIn, uint8_t clock)
    : m_reset(reset)
    , m_sce(chipEnable)
    , m_dc(dataSelect)
    , m_sdin(dataIn)
    , m_sclk(clock)
{
}

void NokiaDisplay::Initialize()
{
    // All pins are outputs
    pinMode(m_sclk,  OUTPUT);
    pinMode(m_sdin,  OUTPUT);
    pinMode(m_dc,    OUTPUT);
    pinMode(m_reset, OUTPUT);
    pinMode(m_sce,   OUTPUT);

    // Reset the controller state
    digitalWrite(m_reset, HIGH);
    digitalWrite(m_sce,   HIGH);
    digitalWrite(m_reset, LOW);
    delay(100);
    digitalWrite(m_reset, HIGH);

    // Set the LCD parameters
    Send(OpType::CMD, 0x21);  // extended instruction set control (H=1)
    Send(OpType::CMD, 0x13);  // bias system (1:48)

    Send(OpType::CMD, 0xc2);  // default Vop (3.06 + 66 * 0.06 = 7V)

    Send(OpType::CMD, 0x20);  // extended instruction set control (H=0)
    Send(OpType::CMD, 0x09);  // all display segments on

    // Clear RAM on Display
    Clear();

    // Activate LCD
    Send(OpType::CMD, 0x08);  // display blank
    Send(OpType::CMD, 0x0c);  // normal mode (0x0d = inverse mode)
    delay(100);

    // Place the cursor at the origin...
    Send(OpType::CMD, 0x80);
    Send(OpType::CMD, 0x40);
}

void NokiaDisplay::Clear()
{
    SetCursor(0, 0);

    for (auto&& i = 0; i < WIDTH * (HEIGHT / 8); i++)
        Send(OpType::DATA, 0x00);

    SetCursor(0, 0);
}

void NokiaDisplay::ClearLine()
{
    SetCursor(m_line, m_column);

    for (uint8_t&& i = 0; i < WIDTH; i++)
        Send(OpType::DATA, 0x00);

    SetCursor(m_line, m_column);
}

void NokiaDisplay::TurnOff()
{
    Send(OpType::CMD, 24);
}

void NokiaDisplay::TurnOn()
{
    Send(OpType::CMD, 20);
}

void NokiaDisplay::SetContrast(uint8_t level)
{
    // The PCD8544 datasheet specifies a maximum Vop of 8.5V
    if (level > 90)
        level = 90;  // Vop = 3.06 + 90 * 0.06 = 8.46V

    Send(OpType::CMD, 0x21);  // extended instruction set control (H=1)
    Send(OpType::CMD, 0x80 | (level & 0x7f));
    Send(OpType::CMD, 0x20);  // extended instruction set control (H=0)
}

void NokiaDisplay::SetCursor(uint8_t line, uint8_t column)
{
	m_isCursorValid = (line < MAX_LINES_COUNT) ? true : false;
	if (!m_isCursorValid)
        return;

    m_column = (column % WIDTH);
    m_line = (line % (HEIGHT / 9 + 1));

    Send(OpType::CMD, 0x80 | m_column);
    Send(OpType::CMD, 0x40 | m_line);
}

void NokiaDisplay::Write(const char* text)
{
	if (!m_isCursorValid)
        return;

    // Write char by char
    while (*text)
        WriteChar(*text++);
}

void NokiaDisplay::Write(char character)
{
    WriteChar(character);
}

void NokiaDisplay::Write(const String& text)
{
	Write(text.c_str());
}

void NokiaDisplay::Write(uint32_t number)
{
    // Write digit by digit, from front
    for (uint8_t i = GetDigitsCount(number); i > 0; --i)
    {
        uint32_t moduloBy = ceil(pow(10, i));
        WriteDigit((number % moduloBy) / (moduloBy / 10));
    }
}

void NokiaDisplay::Write(uint8_t line, const char* text, Aligned aligned)
{
    SetCursor(line, ColumnPixelPosition(SizeInPixels(text), aligned));
    Write(text);
}

void NokiaDisplay::Write(uint8_t line, const String& text, Aligned aligned)
{
    SetCursor(line, ColumnPixelPosition(SizeInPixels(text.c_str()), aligned));
    Write(text);
}

void NokiaDisplay::Write(uint8_t line, uint32_t number, Aligned aligned)
{
    SetCursor(line, ColumnPixelPosition(SizeInPixels(number), aligned));
    Write(number);
}

void NokiaDisplay::WriteChar(uint8_t character)
{
    if (character >= 0x80)
        return;

    for (uint8_t i = 0; i < 5; i++)
        Send(OpType::DATA, pgm_read_byte_near(&ASCII[character - 0x20][i]));

    Send(OpType::DATA, 0x00);

    UpdateCursor();
}

void NokiaDisplay::WriteDigit(uint8_t digit)
{
    if (digit < 0 || digit > 0x9)
        return;

    for (uint8_t i = 0; i < 5; i++)
        Send(OpType::DATA, pgm_read_byte_near(&ASCII[0x10 + digit][i]));

    Send(OpType::DATA, 0x00);

    UpdateCursor();
}

uint8_t NokiaDisplay::SizeInPixels(const char* text) const
{
    const uint8_t length = strlen(text);
    return (length * 5) + (length - 1);
}

uint8_t NokiaDisplay::SizeInPixels(uint32_t number) const
{
    const uint8_t digitsCount = GetDigitsCount(number);
    return (digitsCount * 5) + (digitsCount - 1);
}

uint8_t NokiaDisplay::ColumnPixelPosition(uint8_t sizeInPixels, Aligned aligned) const
{
    switch (aligned)
    {
        case Aligned::Left: return 6; // after the cursor
        case Aligned::Center: return (WIDTH - sizeInPixels) / 2;
        case Aligned::Right: return (WIDTH - sizeInPixels);
    }

    return 0;
}

void NokiaDisplay::Send(OpType type, uint8_t data)
{
    digitalWrite(m_dc, (uint8_t)type); // DC pin is LOW for commands
    digitalWrite(m_sce, LOW);
    shiftOut(m_sdin, m_sclk, MSBFIRST, data);
    digitalWrite(m_sce, HIGH);
}

void NokiaDisplay::UpdateCursor()
{
    // Update the cursor position
    m_column = (m_column + 6) % WIDTH;

    // Next line?
    if (m_column == 0)
        m_line = (m_line + 1) % (HEIGHT / 9 + 1);
}