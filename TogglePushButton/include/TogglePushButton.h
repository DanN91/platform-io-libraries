#pragma once

#include "IPushButtonObserver.h"

class TogglePushButton final
{
public:
    TogglePushButton(uint8_t pin, IPushButtonObserver& observer);
    void Initialize() const;

    void HandleEvents();

private:
    const uint8_t m_pin;
    IPushButtonObserver& m_observer;
};