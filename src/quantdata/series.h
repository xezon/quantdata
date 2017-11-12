
#pragma once

#include "series_tpl.h"

namespace quantdata {

class CDefaultSeries : public IQuantDataSeries
{
protected:
	EQuantDataResult SetApiKey(TQuantDataString apikey);
	EQuantDataResult GetSupportedIntervals(TQuantDataIntervals* pIntervals);
	EQuantDataResult GetSupportedSymbols(TQuantDataSymbols* pSymbols);
	EQuantDataResult Download(TQuantDataDownloadSettings* pSettings);
	EQuantDataResult Load(TQuantDataLoadSettings* pSettings);
	EQuantDataResult Save(TQuantDataSaveSettings* pSettings) const;
	EQuantDataResult GetT1(TQuantDataT1s* pData) const;
	EQuantDataResult GetT2(TQuantDataT2s* pData) const;
	EQuantDataResult GetT6(TQuantDataT6s* pData) const;
	EQuantDataResult GetT8(TQuantDataT8s* pData) const;
	EQuantDataResult GetGtData(TQuantDataGtDataPoints* pData) const;
	EQuantDataResult SetT1(TQuantDataT1s* pData);
	EQuantDataResult SetT2(TQuantDataT2s* pData);
	EQuantDataResult SetT6(TQuantDataT6s* pData);
	EQuantDataResult SetT8(TQuantDataT8s* pData);
	EQuantDataResult SetGtData(TQuantDataGtDataPoints* pData);
	EQuantDataResult Release();
};

using TDefaultSeries = CQuantDataSeriesTpl<CDefaultSeries>;

} // namespace quantdata
