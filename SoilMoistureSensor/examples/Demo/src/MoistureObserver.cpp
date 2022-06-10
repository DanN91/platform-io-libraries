/*
    MoistureObserver: handles SoilMoistureEvent notifications.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "MoistureObserver.h"

#include <SoilMoistureSensor.h>

MoistureObserver::MoistureObserver(SoilMoistureSensor& soilMoistureSensor)
    : IObserver<SoilMoistureEvent>(SoilMoistureEvent::MoistureChanged, soilMoistureSensor)
    , m_soilMoistureSensor(soilMoistureSensor)
{
    IObserver<SoilMoistureEvent>::Register();
}

MoistureObserver::~MoistureObserver()
{
    IObserver<SoilMoistureEvent>::Unregister();
}

void MoistureObserver::OnEvent(SoilMoistureEvent event)
{
    // just display the soil moisture percentage
    const auto moisturePercent = m_soilMoistureSensor.Value();
    const auto moistureValue = m_soilMoistureSensor.RawValue();

    Serial.print("Moisture: ");
    Serial.print(moisturePercent);
    Serial.print(" %");
    Serial.print(" | ");
    Serial.println(moistureValue);
}