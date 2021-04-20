/*
    MenuCursor: range-based cursor which observes a pushbutton and draws a cursor on a Nokia 5110 display on the current line.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "MenuCursor.h"

MenuCursor::MenuCursor(NokiaDisplay& display, PushButton& button, char cursor)
    : m_display(display)
    , m_generator(2, 5, button)
    , m_cursor(cursor)
{
}

void MenuCursor::Refresh()
{
    if (const auto newIndex = m_generator.Value(); newIndex != m_lastIndex)
    {
        Erase();
        Draw(newIndex);
    }
}

void MenuCursor::Draw(uint8_t lineIndex)
{
    if (m_lastIndex == lineIndex)
        return;

    m_lastIndex = lineIndex;
    m_display.SetCursor(m_lastIndex, 0);
    m_display.Write(m_cursor);
}

void MenuCursor::Erase() const
{
    m_display.SetCursor(m_lastIndex, 0);
    m_display.Write(" "); // whitespace
}