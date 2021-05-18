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
    ValuesRange(uint32_t min, uint32_t max)
        : minVal(min)
        , maxVal(max)
    {}

    uint32_t Min() const { return minVal; }
    uint32_t Max() const { return maxVal; }

    bool IsInRange(uint32_t value) const { return value >= Min() && value <= Max(); }

    explicit operator bool() const noexcept { return Min() < Max(); }

private:
    uint32_t minVal = 0;
    uint32_t maxVal = 0;
};

class RangeValuesGenerator final : public IObserver<ButtonState>
{
public:
    RangeValuesGenerator(ValuesRange range, uint32_t step, uint32_t start, IObservable<ButtonState>& button, ButtonState event = ButtonState::Pressed);
    ~RangeValuesGenerator() = default;

    // IObserver<ButtonState>
    void OnEvent(ButtonState event) override;

    [[nodiscard]]
    uint32_t Value() const;

    void Range(ValuesRange range, uint32_t start);

    [[nodiscard]]
    ValuesRange Range() const;

    [[nodiscard]]
    bool IsValid() const;

private:
    ValuesRange m_range;
    uint32_t m_step = 0;
    uint32_t m_current = 0;
};