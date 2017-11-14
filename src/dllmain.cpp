
#include <Windows.h>
#include "quantdata/series.h"
#include <common/utils.h>

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
	return EQuantDataResult::Failure;
}

EQuantDataResult QUANTDATA_CALL QuantDataCleanup()
{
	if (g_quantDataInit)
	{
		curl_global_cleanup();
		g_quantDataInit = false;
		return EQuantDataResult::Success;
	}
	return EQuantDataResult::Failure;
}

EQuantDataResult QUANTDATA_CALL QuantDataCreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings)
{
	if (!g_quantDataInit)
		return EQuantDataResult::NotInitialized;

	if (!ppSeries || !pSettings)
		return EQuantDataResult::InvalidArgument;

	TQuantDataAlloc alloc = pSettings->alloc;
	TQuantDataFree free = pSettings->free;

	if (!alloc || !free)
	{
		alloc = quantdata::GetDefaultAlloc();
		free = quantdata::GetDefaultFree();
	}

	*ppSeries = utils::PlacementAlloc<quantdata::CSeries>(alloc, alloc, free);
	return EQuantDataResult::Success;
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesSetProvider(IQuantDataSeries* pSeries, const TQuantDataProviderSettings* pSettings)
{
	return static_cast<quantdata::CSeries*>(pSeries)->SetProvider(pSettings);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesGetSupportedIntervals(IQuantDataSeries* pSeries, TQuantDataIntervals** ppIntervals)
{
	return static_cast<quantdata::CSeries*>(pSeries)->GetSupportedIntervals(ppIntervals);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesGetSupportedSymbols(IQuantDataSeries* pSeries, TQuantDataSymbols** ppSymbols)
{
	return static_cast<quantdata::CSeries*>(pSeries)->GetSupportedSymbols(ppSymbols);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesDownload(IQuantDataSeries* pSeries, const TQuantDataDownloadSettings* pSettings)
{
	return static_cast<quantdata::CSeries*>(pSeries)->Download(pSettings);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesLoad(IQuantDataSeries* pSeries, const TQuantDataLoadSettings* pSettings)
{
	return static_cast<quantdata::CSeries*>(pSeries)->Load(pSettings);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesSave(IQuantDataSeries* pSeries, const TQuantDataSaveSettings* pSettings)
{
	return static_cast<quantdata::CSeries*>(pSeries)->Save(pSettings);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesGetT1(IQuantDataSeries* pSeries, TQuantDataT1s** ppData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->GetT1(ppData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesGetT2(IQuantDataSeries* pSeries, TQuantDataT2s** ppData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->GetT2(ppData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesGetT6(IQuantDataSeries* pSeries, TQuantDataT6s** ppData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->GetT6(ppData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesGetT8(IQuantDataSeries* pSeries, TQuantDataT8s** ppData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->GetT8(ppData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesGetGtick(IQuantDataSeries* pSeries, TQuantDataGtDataPoints** ppData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->GetGtick(ppData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesSetT1(IQuantDataSeries* pSeries, TQuantDataT1s* pData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->SetT1(pData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesSetT2(IQuantDataSeries* pSeries, TQuantDataT2s* pData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->SetT2(pData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesSetT6(IQuantDataSeries* pSeries, TQuantDataT6s* pData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->SetT6(pData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesSetT8(IQuantDataSeries* pSeries, TQuantDataT8s* pData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->SetT8(pData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesSetGtick(IQuantDataSeries* pSeries, TQuantDataGtDataPoints* pData)
{
	return static_cast<quantdata::CSeries*>(pSeries)->SetGtick(pData);
}

EQuantDataResult QUANTDATA_CALL QuantDataSeriesRelease(IQuantDataSeries* pSeries)
{
	return static_cast<quantdata::CSeries*>(pSeries)->Release();
}
