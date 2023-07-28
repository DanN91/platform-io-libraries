/*
    ILEDController: Simple interface controlling one or many LED(s).
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>

#include "ILEDBlinkConfiguration.h"

class ILEDController
{
public:
    ILEDController() = default;
    virtual ~ILEDController(){};

    virtual void Initialize() = 0;

    virtual void Configure(ILEDBlinkConfiguration* configuration) = 0;
    virtual bool HasFinished() const = 0;

    void SafeRun(); // does nothing if instance is invalid
    virtual explicit operator bool() const = 0; // must be called before using any of the public methods

    void Chain(ILEDController *const);

    // non-copyable & non-movable
    ILEDController(const ILEDController &) = delete;
    ILEDController &operator=(const ILEDController &) = delete;
    ILEDController(ILEDController &&) = delete;
    ILEDController &operator=(ILEDController &&) = delete;

protected:
    virtual void Run();
    bool CanRun() const;

    ILEDController* m_link = nullptr;
};
