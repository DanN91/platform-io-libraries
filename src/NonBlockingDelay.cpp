#include "NonBlockingDelay.h"

NonBlockingDelay::NonBlockingDelay(unsigned long duration, Runnable &callback)
    : duration_(duration), callback_(callback) {}

void NonBlockingDelay::Handle() {
  if (millis() - start_time_ >= duration_) {
    callback_.Run();
    start_time_ = millis();
  }
}