#include <SettingsManager.h>

SettingsManager::SettingsManager(IStorage& storage, uint8_t MAX_OBSERVERS_COUNT)
    : IObservable(MAX_OBSERVERS_COUNT)
	, m_storage(storage)
{
}

void SettingsManager::FactoryReset()
{
	// default values ( Factory Reset )
	// #TODO:Implement
}

void SettingsManager::PrintAll() const
{
	Serial.println(F("\n*** Settings ***"));

	// #TODO:add

	Serial.println(F("***"));
}
