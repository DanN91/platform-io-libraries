/*
    RangeValuesGenerator: increments value in a set range by whenever the observed push button is released.
    Author: Daniel Nistor
    MIT License, 2021
*/
#pragma once

#include <Arduino.h>

#include <PushButtonMasks.h>
#include <ObserverPattern.h>

class RangeValuesGenerator final : IObserver<ButtonState>
{
public:
    RangeValuesGenerator(uint8_t min, uint8_t max, IObservable<ButtonState>& button);
    ~RangeValuesGenerator() = default;

    // IObserver<ButtonState>
    void OnEvent(ButtonState event) override;

    struct ValuesRange
    {
        uint8_t minVal = 0;
        uint8_t maxVal = 0;

        ValuesRange(uint8_t min, uint8_t max)
            : minVal(min)
            , maxVal(max)
        {}
    };

    [[nodiscard]]
    uint8_t Value() const;

    [[nodiscard]]
    bool Range(uint8_t min, uint8_t max);

    [[nodiscard]]
    ValuesRange Range() const;

private:
    uint8_t m_minimum = 0;
    uint8_t m_maximum = 0;

    uint8_t m_current = 0;
};