#include <SettingsManager.h>

SettingsManager::SettingsManager(IStorage &storage, AddressProvider addressProviderFunc, uint8_t MAX_OBSERVERS_COUNT)
	: IObservable(MAX_OBSERVERS_COUNT)
	, m_storage(storage)
	, m_addressProvider(addressProviderFunc)
{
}

SettingsManager::operator bool() const
{
	return m_addressProvider != nullptr;
}