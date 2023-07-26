/*
    ILEDController: Simple interface controlling one or many LED(s).
    Author: Daniel Nistor
    MIT License, 2023
*/
#include "ILEDController.h"

ILEDController::ILEDController(uint32_t intervalMs)
    : m_intervalMs(intervalMs)
{
}

ILEDController::ILEDController(uint32_t intervalMs, uint8_t times)
    : m_intervalMs(intervalMs)
    , m_times(times)
{
}

void ILEDController::Chain(ILEDController* const ledController)
{
    m_link = ledController;
}

bool ILEDController::CanRun() const
{
    if (!m_link)
        return true;

    return m_link->HasFinished();
}