#include "NonBlockingDelay.h"
#include <Arduino.h>

class SerialPrinter : public Runnable {
public:
  void Run() override {
    Serial.print("Test @ ");
    Serial.println(millis());
  }
};

SerialPrinter printer;
NonBlockingDelay printingDelay(2000, printer);

void setup() {
  Serial.begin(115200);
  Serial.println("Initialized.");
}

void loop() { printingDelay.Handle(); }