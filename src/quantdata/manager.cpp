
#include "manager.h"
#include "quantdata/series.h"

#ifdef _DEBUG
#pragma comment(lib, "libcurl_a_debug.lib")
#else
#pragma comment(lib, "libcurl_a.lib")
#endif

namespace quantdata {

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

	utils::SAllocatorFunctions functions = GetAllocatorFunctions(pSettings);
	*ppSeries = utils::PlacementAlloc<quantdata::CSeries>(functions.alloc, *this, functions);

	return EQuantDataResult::Success;
}

utils::SAllocatorFunctions CManager::GetAllocatorFunctions(const TQuantDataCreationSettings* pSettings)
{
	TQuantDataAlloc alloc = pSettings->alloc;
	TQuantDataFree free = pSettings->free;

	if (!alloc || !free)
	{
		alloc = quantdata::GetDefaultAlloc();
		free = quantdata::GetDefaultFree();
	}

	return utils::SAllocatorFunctions(alloc, free);
}

} // namespace quantdata
