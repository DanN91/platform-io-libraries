/*
    ILEDController: Simple interface controlling one or many LED(s).
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>

class ILEDController
{
public:
  ILEDController() = default;
  ILEDController(uint32_t intervalMs);
  ILEDController(uint32_t intervalMs, uint8_t times);
  virtual ~ILEDController() {};

  virtual void Initialize() = 0;

  virtual void Configure(uint32_t intervalMs, uint8_t times) = 0;
  virtual void Run();
  virtual bool HasFinished() const = 0;

  void Chain(ILEDController* const);

  // non-copyable & non-movable
  ILEDController(const ILEDController &) = delete;
  ILEDController &operator=(const ILEDController &) = delete;
  ILEDController(ILEDController &&) = delete;
  ILEDController &operator=(ILEDController &&) = delete;

protected:
  bool CanRun() const;

  uint32_t m_intervalMs = 0;
  uint8_t m_times = 1;
  uint8_t m_countTimes = 0;
  uint32_t m_lastMs = 0;

  ILEDController* m_link = nullptr;
};
