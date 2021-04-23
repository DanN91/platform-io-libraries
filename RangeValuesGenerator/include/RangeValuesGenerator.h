/*
    RangeValuesGenerator: increments value in a set range by whenever the observed push button is released.
    Author: Daniel Nistor
    MIT License, 2021
*/
#pragma once

#include <Arduino.h>

#include <PushButtonMasks.h>
#include <ObserverPattern.h>

struct ValuesRange
{
    ValuesRange(uint16_t min, uint16_t max)
        : minVal(min)
        , maxVal(max)
    {}

    uint16_t Min() const { return minVal; }
    uint16_t Max() const { return maxVal; }

    bool IsInRange(uint16_t value) const { return value >= Min() && value <= Max(); }

    explicit operator bool() const noexcept { return Min() < Max(); }

private:
    uint16_t minVal = 0;
    uint16_t maxVal = 0;
};

class RangeValuesGenerator final : IObserver<ButtonState>
{
public:
    RangeValuesGenerator(ValuesRange range, uint8_t step, uint16_t start, IObservable<ButtonState>& button);
    ~RangeValuesGenerator() = default;

    // IObserver<ButtonState>
    void OnEvent(ButtonState event) override;

    [[nodiscard]]
    uint16_t Value() const;

    void Range(ValuesRange range);

    [[nodiscard]]
    ValuesRange Range() const;

    [[nodiscard]]
    bool IsValid() const;

private:
    ValuesRange m_range;
    uint8_t m_step = 0;

    uint16_t m_current = 0;
};