#pragma once

class IStopwatchHandler
{
public:
    virtual ~IStopwatchHandler() {};

    // Interface
    virtual void OnStart() = 0;
    virtual void OnStop() = 0;
};