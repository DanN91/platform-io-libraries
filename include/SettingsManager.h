#pragma once

#include <Arduino.h>

#include <IStorage.h>
#include <ObserverPattern.h>

#include "SettingsMasks.h"

class SettingsManager final : public IObservable<Settings>
{
public:
	SettingsManager(IStorage& storage, uint8_t MAX_OBSERVERS_COUNT = 1);
	~SettingsManager() = default;

	template<typename T>
	bool Set(Settings setting, T value)
	{
		if (!m_storage.write(GetAddress(setting), value))
			return false;

		Notify(setting);
		return true;
	}
	
	template<typename T>
	bool Get(Settings setting, T& buffer) const
	{
		return m_storage.read(GetAddress(setting), buffer);
	}

	// all
	void FactoryReset();
	void PrintAll() const;

	// non-copyable & non-movable
	SettingsManager(const SettingsManager&) = delete;
	SettingsManager& operator=(const SettingsManager&) = delete;
	SettingsManager(SettingsManager&&) = delete;
	SettingsManager& operator=(SettingsManager&&) = delete;

private:
	uint16_t GetAddress(Settings setting) const
	{
		switch (setting)
		{
			// all float = 4 bytes
			case Settings::TemperatureMin:
				return 0;
			case Settings::TemperatureMax:
				return 4;
			case Settings::HumidityMin:
				return 8;
			case Settings::HumidityMax:
				return 12;
		}
	}

	IStorage& m_storage;
};