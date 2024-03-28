/*
    ISwitch: Interface exposing methods for turning On and Off a device
    #TODO:add details here and move to platform-io-libraries repo + use as a dependency
*/

#pragma once

class ISwitch
{
public:
    ISwitch(bool useLowLevel = false);
    virtual ~ISwitch() = default;

    virtual void On();
    virtual void Off();

    bool IsOn() const;

protected:
    const bool m_useLowLevel = false;

private:
    bool m_isSwitchOn = false;
};