
#include "manager.h"
#include <quantdata/series.h>
#include <common/util.h>
#include <algorithm>

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

template <class AllocatorFunctions>
using TSeries = CSeriesFunctions<CSeries<AllocatorFunctions>>;

EQuantDataResult CManager::CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings)
{
	if (!ppSeries || !pSettings)
		return EQuantDataResult::InvalidArgument;

	const auto alloc = pSettings->alloc;
	const auto free = pSettings->free;

	if (alloc && free)
	{
		mem::custom_allocator_functions functions(alloc, free);
		*ppSeries = mem::placement_alloc<TSeries<decltype(functions)>>(functions.alloc(), functions, *this);
	}
	else
	{
		mem::regular_allocator_functions functions;
		*ppSeries = mem::placement_alloc<TSeries<decltype(functions)>>(functions.alloc(), functions, *this);
	}

	return EQuantDataResult::Success;
}

} // namespace quantdata
