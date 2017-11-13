
#include <Windows.h>
#include "quantdata/series.h"
#include <utils.h>

#ifdef _DEBUG
#pragma comment(lib, "libcurl_a_debug.lib")
#else
#pragma comment(lib, "libcurl_a.lib")
#endif

bool g_quantDataInit = false;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	(void)hinstDLL;
	(void)fdwReason;
	(void)lpvReserved;
	return TRUE;
}

EQuantDataResult QUANTDATA_CALL QuantDataInit()
{
	if (!g_quantDataInit)
	{
		if (curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK)
		{
			g_quantDataInit = true;
			return EQuantDataResult::Success;
		}
	}
	return EQuantDataResult::InitFailed;
}

EQuantDataResult QUANTDATA_CALL QuantDataCleanup()
{
	if (g_quantDataInit)
	{
		curl_global_cleanup();
		g_quantDataInit = false;
		return EQuantDataResult::Success;
	}
	return EQuantDataResult::InitFailed;
}

EQuantDataResult QUANTDATA_CALL QuantDataCreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings)
{
	if (!ppSeries || !pSettings)
		return EQuantDataResult::InvalidArgument;

	TQuantDataAlloc alloc = pSettings->alloc;
	TQuantDataFree free = pSettings->free;

	if (!alloc || !free)
	{
		alloc = quantdata::GetDefaultAlloc();
		free = quantdata::GetDefaultFree();
	}

	*ppSeries = utils::PlacementAlloc<quantdata::TSeries>(alloc, alloc, free);
	return EQuantDataResult::Success;
}
