/*
    MenuCursor: range-based cursor which observes a pushbutton and draws a cursor on a Nokia 5110 display on the current line.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

#include <NokiaDisplay.h>
#include <PushButton.h>
#include <RangeValuesGenerator.h>

class MenuCursor final
{
public:
    MenuCursor(NokiaDisplay& display, PushButton& button, char cursor);
    ~MenuCursor() = default;

    void Refresh();

    // non-copyable & non-movable
    MenuCursor(const MenuCursor&) = delete;
    MenuCursor& operator=(const MenuCursor&) = delete;
    MenuCursor(MenuCursor&&) = delete;
    MenuCursor& operator=(MenuCursor&&) = delete;

private:
    void Draw(uint8_t lineIndex);
    void Erase() const;

    NokiaDisplay& m_display;
    RangeValuesGenerator m_generator;
    uint8_t m_lastIndex = 255;
    const char m_cursor = '>';
};