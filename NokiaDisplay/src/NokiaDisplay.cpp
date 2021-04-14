// 
// 
// 
#include "NokiaDisplay.h"
#include "font.h"

namespace
{
    const byte width = 84;
    const byte height = 48;
	const byte MAX_LINES_COUNT = 6;
}

NokiaDisplay::NokiaDisplay(byte reset, byte chipEnable, byte dataSelect, byte dataIn, byte clock)
    : m_reset(reset)
    , m_sce(chipEnable)
    , m_dc(dataSelect)
    , m_sdin(dataIn)
    , m_sclk(clock)
{
}

NokiaDisplay& NokiaDisplay::getInstance(byte reset, byte chipEnable, byte dataSelect, byte dataIn, byte clock)
{
    static NokiaDisplay instance(reset, chipEnable, dataSelect, dataIn, clock);
    return instance;
}

void NokiaDisplay::initialize()
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
    send(OpType::CMD, 0x21);  // extended instruction set control (H=1)
    send(OpType::CMD, 0x13);  // bias system (1:48)

    send(OpType::CMD, 0xc2);  // default Vop (3.06 + 66 * 0.06 = 7V)

    send(OpType::CMD, 0x20);  // extended instruction set control (H=0)
    send(OpType::CMD, 0x09);  // all display segments on

    // Clear RAM on Display
    clear();

    // Activate LCD
    send(OpType::CMD, 0x08);  // display blank
    send(OpType::CMD, 0x0c);  // normal mode (0x0d = inverse mode)
    delay(100);

    // Place the cursor at the origin...
    send(OpType::CMD, 0x80);
    send(OpType::CMD, 0x40);
}

void NokiaDisplay::clear()
{
    setCursor(0, 0);

    for (auto&& i = 0; i < width * (height / 8); i++)
    {
        send(OpType::DATA, 0x00);
    }

    setCursor(0, 0);
}

void NokiaDisplay::clearLine()
{
    setCursor(m_line, m_column);

    for (byte&& i = 0; i < width; i++)
        send(OpType::DATA, 0x00);

    setCursor(m_line, m_column);
}

void NokiaDisplay::setContrast(byte level)
{
    // The PCD8544 datasheet specifies a maximum Vop of 8.5V
    if (level > 90)
    {
        level = 90;  // Vop = 3.06 + 90 * 0.06 = 8.46V
    }

    send(OpType::CMD, 0x21);  // extended instruction set control (H=1)
    send(OpType::CMD, 0x80 | (level & 0x7f));
    send(OpType::CMD, 0x20);  // extended instruction set control (H=0)
}

void NokiaDisplay::setCursor(byte line, byte column)
{
	m_isCursorValid = (line < MAX_LINES_COUNT) ? true : false;
	if (m_isCursorValid)
	{
		m_column = (column % width);
		m_line = (line % (height / 9 + 1));

		send(OpType::CMD, 0x80 | m_column);
		send(OpType::CMD, 0x40 | m_line);
	}
}

void NokiaDisplay::write(const char* text)
{
	if (m_isCursorValid)
	{
		// Write char by char
		while (*text)
			writeChar(*text++);
	}
}

void NokiaDisplay::write(String&& text)
{
	write(text.c_str());
}

void NokiaDisplay::write(String& text)
{
	write(text.c_str());
}

void NokiaDisplay::write(uint32_t number)
{
    // number of digits
    uint8_t nrOfDigits = 0;
    auto temp = number;
    while (temp > 0)
    {
        temp /= 10;
        nrOfDigits++;
    }

    // write digit by digit, from front
    while (nrOfDigits > 0)
    {
        uint32_t moduloBy = ceil(pow(10, nrOfDigits));
        writeDigit((number % moduloBy) / (moduloBy / 10));
        nrOfDigits--;
    }
}

void NokiaDisplay::writeChar(byte character)
{
    if (character >= 0x80)
        return;

    for (byte i = 0; i < 5; i++)
        send(OpType::DATA, pgm_read_byte_near(&ASCII[character - 0x20][i]));

    send(OpType::DATA, 0x00);

    // Update the cursor position
    m_column = (m_column + 6) % width;

    // Next line?
    if (m_column == 0)
        m_line = (m_line + 1) % (height / 9 + 1);
}

void NokiaDisplay::writeDigit(byte digit)
{
    if (digit < 0 || digit > 0x9)
        return;

    for (byte i = 0; i < 5; i++)
        send(OpType::DATA, pgm_read_byte_near(&ASCII[0x10 + digit][i]));

    send(OpType::DATA, 0x00);

    // Update the cursor position
    m_column = (m_column + 6) % width;

    // Next line?
    if (m_column == 0)
        m_line = (m_line + 1) % (height / 9 + 1);
}

void NokiaDisplay::send(OpType type, byte data)
{
    digitalWrite(m_dc, (uint8_t)type); // DC pin is LOW for commands
    digitalWrite(m_sce, LOW);
    shiftOut(m_sdin, m_sclk, MSBFIRST, data);
    digitalWrite(m_sce, HIGH);
}
