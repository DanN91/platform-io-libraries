#pragma once

#include "Runnable.h"
#include <Arduino.h>

class NonBlockingDelay final {
public:
  NonBlockingDelay(unsigned long duration, Runnable &callback);

  void Handle();

private:
  unsigned long start_time_ = millis();
  unsigned long duration_;
  Runnable &callback_;
};