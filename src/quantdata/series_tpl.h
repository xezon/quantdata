
#pragma once

#include "quantdata.h"
#include <utils.h>

namespace quantdata {

template <class SeriesImpl>
class CQuantDataSeriesTpl : public SeriesImpl
{
public:
	CQuantDataSeriesTpl(TQuantDataAlloc alloc, TQuantDataFree free)
		: SeriesImpl(alloc, free)
	{
		SQuantDataSeriesFunctions& mutableFunctions = const_cast<SQuantDataSeriesFunctions&>(functions);
		memset(&mutableFunctions, 0, sizeof(mutableFunctions));

		mutableFunctions.SetProvider           = Static_SetProvider;
		mutableFunctions.GetSupportedIntervals = Static_GetSupportedIntervals;
		mutableFunctions.GetSupportedSymbols   = Static_GetSupportedSymbols;
		mutableFunctions.Download              = Static_Download;
		mutableFunctions.Load                  = Static_Load;
		mutableFunctions.Save                  = Static_Save;
		mutableFunctions.GetT1                 = Static_GetT1;
		mutableFunctions.GetT2                 = Static_GetT2;
		mutableFunctions.GetT6                 = Static_GetT6;
		mutableFunctions.GetT8                 = Static_GetT8;
		mutableFunctions.GetGtick              = Static_GetGtick;
		mutableFunctions.SetT1                 = Static_SetT1;
		mutableFunctions.SetT2                 = Static_SetT2;
		mutableFunctions.SetT6                 = Static_SetT6;
		mutableFunctions.SetT8                 = Static_SetT8;
		mutableFunctions.SetGtick              = Static_SetGtick;
		mutableFunctions.Release               = Static_Release;

		::utils::VerifyFunctionsStruct(functions);
		::utils::VerifyEqualPointers(&functions, static_cast<IQuantDataSeries*>(this));
	}

private:
	UTILS_DELETE_COPY_CONSTRUCTOR(CQuantDataSeriesTpl)

private:
	static EQuantDataResult QUANTDATA_CALL Static_SetProvider(IQuantDataSeries* pThis, const TQuantDataProviderSettings* pSettings) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->SetProvider(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetSupportedIntervals(IQuantDataSeries* pThis, TQuantDataIntervals* pIntervals) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->GetSupportedIntervals(pIntervals);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetSupportedSymbols(IQuantDataSeries* pThis, TQuantDataSymbols* pSymbols) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->GetSupportedSymbols(pSymbols);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Download(IQuantDataSeries* pThis, const TQuantDataDownloadSettings* pSettings) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->Download(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Load(IQuantDataSeries* pThis, const TQuantDataLoadSettings* pSettings) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->Load(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Save(IQuantDataSeries* pThis, const TQuantDataSaveSettings* pSettings) {
		return static_cast<const CQuantDataSeriesTpl*>(pThis)->Save(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetT1(IQuantDataSeries* pThis, TQuantDataT1s* pData) {
		return static_cast<const CQuantDataSeriesTpl*>(pThis)->GetT1(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetT2(IQuantDataSeries* pThis, TQuantDataT2s* pData) {
		return static_cast<const CQuantDataSeriesTpl*>(pThis)->GetT2(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetT6(IQuantDataSeries* pThis, TQuantDataT6s* pData) {
		return static_cast<const CQuantDataSeriesTpl*>(pThis)->GetT6(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetT8(IQuantDataSeries* pThis, TQuantDataT8s* pData) {
		return static_cast<const CQuantDataSeriesTpl*>(pThis)->GetT8(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetGtick(IQuantDataSeries* pThis, TQuantDataGtDataPoints* pData) {
		return static_cast<const CQuantDataSeriesTpl*>(pThis)->GetGtick(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetT1(IQuantDataSeries* pThis, TQuantDataT1s* pData) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->SetT1(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetT2(IQuantDataSeries* pThis, TQuantDataT2s* pData) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->SetT2(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetT6(IQuantDataSeries* pThis, TQuantDataT6s* pData) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->SetT6(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetT8(IQuantDataSeries* pThis, TQuantDataT8s* pData) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->SetT8(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetGtick(IQuantDataSeries* pThis, TQuantDataGtDataPoints* pData) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->SetGtick(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Release(IQuantDataSeries* pThis) {
		return static_cast<CQuantDataSeriesTpl*>(pThis)->Release();
	}
};

} // namespace quantdata
