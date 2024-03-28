/*
    ISwitch: Interface exposing methods for turning On and Off a device
    #TODO:add details here and move to platform-io-libraries repo + use as a dependency
*/

#include "ISwitch.h"

ISwitch::ISwitch(bool useLowLevel)
    : m_useLowLevel(useLowLevel)
{
}

void ISwitch::On()
{
    m_isSwitchOn = true;
}

void ISwitch::Off()
{
    m_isSwitchOn = false;
}

bool ISwitch::IsOn() const
{
    return m_isSwitchOn;
}