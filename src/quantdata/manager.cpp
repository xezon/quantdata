
#include "manager.h"
#include <quantdata/hub.h>
#include <common/util.h>
#include <common/mem.h>

DEFINE_GLOBAL_ALLOC_FUNCTIONS

namespace quantdata {

CManager::CManager()
{
	const auto& providerUrls   = internal::GetProviderUrls();
	auto providerPeriods       = internal::BuildProviderPeriods();
	auto providerSymbolSources = internal::BuildProviderSymbolSources();
	auto providerSymbolsList   = internal::BuildProviderSymbolsList();

	for (CQuantDataProvider provider : CQuantDataProvider())
	{
		const auto ordinal         = provider.ordinal();
		auto& providerInfo         = m_providerInfos[ordinal];
		providerInfo.url           = providerUrls[ordinal];
		providerInfo.periods       = std::move(providerPeriods[ordinal]);
		providerInfo.symbolSources = std::move(providerSymbolSources[ordinal]);
		providerInfo.symbolsList   = std::move(providerSymbolsList[ordinal]);
	}
}

EQuantDataResult CManager::SetAllocator(const TQuantDataAllocatorSettings* pSettings)
{
	if (m_allocatorInUse)
		return EQuantDataResult::LockedAllocator;

	if (!pSettings->alloc || !pSettings->free)
		return EQuantDataResult::IncompleteAllocator;

	mem::g_alloc = pSettings->alloc;
	mem::g_free = pSettings->free;

	return EQuantDataResult::Success;
}

using THub = CHubFunctions<CHub>;

EQuantDataResult CManager::CreateHub(IQuantDataHub** ppHub)
{
	if (!ppHub)
		return EQuantDataResult::InvalidArgument;

	m_allocatorInUse = true;
	*ppHub = mem::placement_g_alloc<THub>(*this);

	return EQuantDataResult::Success;
}

} // namespace quantdata
