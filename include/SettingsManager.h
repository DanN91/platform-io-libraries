#pragma once

#include <Arduino.h>

#include <IStorage.h>
#include <ObserverPattern.h>

#include "SettingsMasks.h"

typedef uint16_t (*AddressProvider) (Settings);

class SettingsManager final : public IObservable<Settings>
{
public:
	SettingsManager(IStorage& storage, AddressProvider addressProviderFunc, uint8_t MAX_OBSERVERS_COUNT = 1);
	~SettingsManager() = default;

	template<typename T>
	bool Set(Settings setting, const T& value)
	{
		if (!(*this))
			return false;

		if (!m_storage.write(m_addressProvider(setting), value))
			return false;

		Notify(setting);
		return true;
	}
	
	template<typename T>
	bool Get(Settings setting, T& buffer) const
	{
		if (!(*this))
			return false;

		return m_storage.read(m_addressProvider(setting), buffer);
	}

	bool Clear(Settings setting, uint16_t size) const
	{
		if (!(*this))
			return false;

		return m_storage.clear(m_addressProvider(setting), size);
	}

	explicit operator bool() const;

	// non-copyable & non-movable
	SettingsManager(const SettingsManager&) = delete;
	SettingsManager& operator=(const SettingsManager&) = delete;
	SettingsManager(SettingsManager&&) = delete;
	SettingsManager& operator=(SettingsManager&&) = delete;

private:
	IStorage& m_storage;
	AddressProvider m_addressProvider = nullptr;
};