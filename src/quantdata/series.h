
#pragma once

#include "series_tpl.h"

namespace quantdata {

class CQuantDataSeries : public IQuantDataSeries
{
protected:
	EQuantDataResult SetProvider(TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetSupportedIntervals(TQuantDataIntervals* pIntervals);
	EQuantDataResult GetSupportedSymbols(TQuantDataSymbols* pSymbols);
	EQuantDataResult Download(TQuantDataDownloadSettings* pSettings);
	EQuantDataResult Load(TQuantDataLoadSettings* pSettings);
	EQuantDataResult Save(TQuantDataSaveSettings* pSettings) const;
	EQuantDataResult GetT1(TQuantDataT1s* pData) const;
	EQuantDataResult GetT2(TQuantDataT2s* pData) const;
	EQuantDataResult GetT6(TQuantDataT6s* pData) const;
	EQuantDataResult GetT8(TQuantDataT8s* pData) const;
	EQuantDataResult GetGtick(TQuantDataGtDataPoints* pData) const;
	EQuantDataResult SetT1(TQuantDataT1s* pData);
	EQuantDataResult SetT2(TQuantDataT2s* pData);
	EQuantDataResult SetT6(TQuantDataT6s* pData);
	EQuantDataResult SetT8(TQuantDataT8s* pData);
	EQuantDataResult SetGtick(TQuantDataGtDataPoints* pData);
	EQuantDataResult Release();
};

using TSeries = CQuantDataSeriesTpl<CQuantDataSeries>;

} // namespace quantdata
