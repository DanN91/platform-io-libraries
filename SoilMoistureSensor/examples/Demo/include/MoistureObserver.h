/*
    MoistureObserver: handles SoilMoistureEvent notifications.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <ObserverPattern.h>
#include <SoilMoistureMasks.h>

class SoilMoistureSensor;

class MoistureObserver final : public IObserver<SoilMoistureEvent>
{
public:
    MoistureObserver(SoilMoistureSensor& soilMoistureSensor);
    virtual ~MoistureObserver();

    // IObserver<SoilMoistureEvent>
    void OnEvent(SoilMoistureEvent event) override;

private:
    SoilMoistureSensor& m_soilMoistureSensor;
};