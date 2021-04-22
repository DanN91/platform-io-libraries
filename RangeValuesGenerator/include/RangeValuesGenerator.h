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
    RangeValuesGenerator(uint16_t min, uint16_t max, uint8_t step, IObservable<ButtonState>& button);
    ~RangeValuesGenerator() = default;

    // IObserver<ButtonState>
    void OnEvent(ButtonState event) override;

    struct ValuesRange
    {
        uint16_t minVal = 0;
        uint16_t maxVal = 0;

        ValuesRange(uint16_t min, uint16_t max)
            : minVal(min)
            , maxVal(max)
        {}
    };

    [[nodiscard]]
    uint16_t Value() const;

    [[nodiscard]]
    bool Range(uint16_t min, uint16_t max);

    [[nodiscard]]
    ValuesRange Range() const;

    [[nodiscard]]
    bool IsValid() const;

private:
    uint16_t m_minimum = 0;
    uint16_t m_maximum = 0;
    uint8_t m_step = 0;
    bool m_isRangeValid = false;

    uint16_t m_current = 0;
};