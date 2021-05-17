/*
    MenuCursor: range-based cursor which observes a pushbutton and draws a cursor on a Nokia 5110 display on the current line.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "MenuCursor.h"

namespace
{
    constexpr const uint8_t LINE_OFFSET = 2;
} // anonymous

MenuCursor::MenuCursor(NokiaDisplay& display, PushButton& button, char cursor, uint8_t items)
    : m_display(display)
    , m_generator({ 0, items }, 1, 0, button)
    , m_cursor(cursor)
{
    button.Register(&m_generator);
}

void MenuCursor::Range(ValuesRange range)
{
    m_generator.Range(range);
}

void MenuCursor::Refresh(bool force)
{
    if (!m_generator.IsValid())
        return;

    if (const auto newIndex = m_generator.Value(); force || newIndex != m_lastIndex)
    {
        Erase();
        Draw(newIndex);
    }
}

uint8_t MenuCursor::Value() const
{
    return m_generator.Value();
}

void MenuCursor::Draw(uint8_t lineIndex)
{
    m_lastIndex = LINE_OFFSET + lineIndex;
    m_display.SetCursor(m_lastIndex, 0);
    m_display.Write(m_cursor);
}

void MenuCursor::Erase() const
{
    m_display.SetCursor(m_lastIndex, 0);
    m_display.Write(" "); // whitespace
}