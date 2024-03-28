/*
    ISwitch: Interface exposing methods for turning On and Off a device
    #TODO:add details here and move to platform-io-libraries repo + use as a dependency
*/

#pragma once

class ISwitch
{
public:
    virtual void On() = 0;
    virtual void Off() = 0;

protected:
    bool m_isSwitchOn = false;
};