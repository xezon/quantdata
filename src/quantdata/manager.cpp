
#include "manager.h"
#include <quantdata/series.h>
#include <common/util.h>

namespace quantdata {

using TSeries = CSeriesFunctions<CSeries>;

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

	mem::custom_allocator_functions functions = GetAllocatorFunctions(pSettings);
	*ppSeries = mem::placement_alloc<quantdata::TSeries>(functions.alloc(), *this, functions);

	return EQuantDataResult::Success;
}

TAllocatorFunctions CManager::GetAllocatorFunctions(const TQuantDataCreationSettings* pSettings)
{
	TQuantDataAlloc alloc = pSettings->alloc;
	TQuantDataFree free = pSettings->free;

	if (!alloc || !free)
	{
		alloc = quantdata::GetDefaultAlloc();
		free = quantdata::GetDefaultFree();
	}

	return TAllocatorFunctions(alloc, free);
}

} // namespace quantdata
