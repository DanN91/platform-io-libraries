/*
    ILEDController: Simple interface controlling one or many LED(s).
    Author: Daniel Nistor
    MIT License, 2023
*/
#include "ILEDController.h"

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

void ILEDController::SafeRun()
{
    if (!(*this))
        return; // do nothing if object is invalid

    Run();
}
