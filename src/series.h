
#pragma once

#include "quantdata.h"

namespace quantdata {

class CQuantDataSeries
	: public IQuantDataSeries
{
public:
	CQuantDataSeries() {}
	~CQuantDataSeries() {}

	CQuantDataSeries(const CQuantDataSeries&) = delete;
	CQuantDataSeries& operator=(const CQuantDataSeries&) = delete;

private:
	static EQuantDataResult QUANTDATA_CALL SetApiKey(IQuantDataSeries* pThis, TQuantDataString apikey) {
		return static_cast<CQuantDataSeries*>(pThis)->SetApiKeyInternal(apikey);
	}
	static EQuantDataResult QUANTDATA_CALL GetSupportedIntervals(IQuantDataSeries* pThis, TQuantDataIntervals* pIntervals) {
		return static_cast<CQuantDataSeries*>(pThis)->GetSupportedIntervalsInternal(pIntervals);
	}
	static EQuantDataResult QUANTDATA_CALL GetSupportedSymbols(IQuantDataSeries* pThis, TQuantDataSymbols* pSymbols) {
		return static_cast<CQuantDataSeries*>(pThis)->GetSupportedSymbolsInternal(pSymbols);
	}
	static EQuantDataResult QUANTDATA_CALL Download(IQuantDataSeries* pThis, TQuantDataDownloadSettings* pSettings) {
		return static_cast<CQuantDataSeries*>(pThis)->DownloadInternal(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Load(IQuantDataSeries* pThis, TQuantDataLoadSettings* pSettings) {
		return static_cast<CQuantDataSeries*>(pThis)->LoadInternal(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Save(IQuantDataSeries* pThis, TQuantDataSaveSettings* pSettings) {
		return static_cast<CQuantDataSeries*>(pThis)->SaveInternal(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL GetT1(IQuantDataSeries* pThis, TQuantDataT1s* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->GetT1Internal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL GetT2(IQuantDataSeries* pThis, TQuantDataT2s* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->GetT2Internal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL GetT6(IQuantDataSeries* pThis, TQuantDataT6s* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->GetT6Internal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL GetT8(IQuantDataSeries* pThis, TQuantDataT8s* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->GetT8Internal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL GetGtData(IQuantDataSeries* pThis, TQuantDataGtDataPoints* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->GetGtDataInternal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL SetT1(IQuantDataSeries* pThis, TQuantDataT1s* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->SetT1Internal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL SetT2(IQuantDataSeries* pThis, TQuantDataT2s* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->SetT2Internal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL SetT6(IQuantDataSeries* pThis, TQuantDataT6s* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->SetT6Internal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL SetT8(IQuantDataSeries* pThis, TQuantDataT8s* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->SetT8Internal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL SetGtData(IQuantDataSeries* pThis, TQuantDataGtDataPoints* pData) {
		return static_cast<CQuantDataSeries*>(pThis)->SetGtDataInternal(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Release(IQuantDataSeries* pThis) {
		return static_cast<CQuantDataSeries*>(pThis)->ReleaseInternal();
	}

	EQuantDataResult SetApiKeyInternal(TQuantDataString apikey);
	EQuantDataResult GetSupportedIntervalsInternal(TQuantDataIntervals* pIntervals);
	EQuantDataResult GetSupportedSymbolsInternal(TQuantDataSymbols* pSymbols);
	EQuantDataResult DownloadInternal(TQuantDataDownloadSettings* pSettings);
	EQuantDataResult LoadInternal(TQuantDataLoadSettings* pSettings);
	EQuantDataResult SaveInternal(TQuantDataSaveSettings* pSettings);
	EQuantDataResult GetT1Internal(TQuantDataT1s* pData);
	EQuantDataResult GetT2Internal(TQuantDataT2s* pData);
	EQuantDataResult GetT6Internal(TQuantDataT6s* pData);
	EQuantDataResult GetT8Internal(TQuantDataT8s* pData);
	EQuantDataResult GetGtDataInternal(TQuantDataGtDataPoints* pData);
	EQuantDataResult SetT1Internal(TQuantDataT1s* pData);
	EQuantDataResult SetT2Internal(TQuantDataT2s* pData);
	EQuantDataResult SetT6Internal(TQuantDataT6s* pData);
	EQuantDataResult SetT8Internal(TQuantDataT8s* pData);
	EQuantDataResult SetGtDataInternal(TQuantDataGtDataPoints* pData);
	EQuantDataResult ReleaseInternal();
};

} // namespace quantdata
