
#include "manager.h"
#include <quantdata/series.h>
#include <common/util.h>

namespace quantdata {

template <class AllocatorFunctions>
using TSeries = CSeriesFunctions<CSeries<AllocatorFunctions>>;

CManager::CManager()
{
	BuildProviderInfos();
}

void CManager::BuildProviderInfos()
{
	for (CQuantDataProvider provider : CQuantDataProvider())
	{
		auto ordinal = provider.ordinal();
		for (CQuantDataPeriod period : CQuantDataPeriod())
		{
			auto apiName = period.meta().apiNames[ordinal];
			if (util::is_valid_string(apiName))
			{
				auto value = period.value();
				m_providerInfos[ordinal].periods.push_back(value);
			}
		}
	}
}

EQuantDataResult CManager::Init()
{
	if (!m_isInitialized)
	{
		if (curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK)
		{
			m_isInitialized = true;
			return EQuantDataResult::Success;
		}
	}
	return EQuantDataResult::Failure;
}

EQuantDataResult CManager::Shutdown()
{
	if (m_isInitialized)
	{
		curl_global_cleanup();
		m_isInitialized = false;
		return EQuantDataResult::Success;
	}
	return EQuantDataResult::Failure;
}

EQuantDataResult CManager::CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings)
{
	if (!m_isInitialized)
		return EQuantDataResult::NotInitialized;

	if (!ppSeries || !pSettings)
		return EQuantDataResult::InvalidArgument;

	auto alloc = pSettings->alloc;
	auto free = pSettings->free;

	if (alloc && free)
	{
		auto functions = mem::custom_allocator_functions(alloc, free);
		*ppSeries = mem::placement_alloc<TSeries<decltype(functions)>>(functions.alloc(), *this, functions);
	}
	else
	{
		auto functions = mem::regular_allocator_functions();
		*ppSeries = mem::placement_alloc<TSeries<decltype(functions)>>(functions.alloc(), *this, functions);
	}

	return EQuantDataResult::Success;
}

} // namespace quantdata
