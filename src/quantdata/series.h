
#pragma once

#include "quantdata.h"

namespace quantdata {

class CSeries : public IQuantDataSeries
{
public:
	CSeries(TQuantDataAlloc alloc, TQuantDataFree free)
		: m_alloc(alloc)
		, m_free(free)
	{}

	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetSupportedIntervals(TQuantDataIntervals** ppIntervals);
	EQuantDataResult GetSupportedSymbols(TQuantDataSymbols** ppSymbols);
	EQuantDataResult Download(const TQuantDataDownloadSettings* pSettings);
	EQuantDataResult Load(const TQuantDataLoadSettings* pSettings);
	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings) const;
	EQuantDataResult GetT1(TQuantDataT1s** ppData) const;
	EQuantDataResult GetT2(TQuantDataT2s** ppData) const;
	EQuantDataResult GetT6(TQuantDataT6s** ppData) const;
	EQuantDataResult GetT8(TQuantDataT8s** ppData) const;
	EQuantDataResult GetGtick(TQuantDataGtDataPoints** ppData) const;
	EQuantDataResult SetT1(TQuantDataT1s* pData);
	EQuantDataResult SetT2(TQuantDataT2s* pData);
	EQuantDataResult SetT6(TQuantDataT6s* pData);
	EQuantDataResult SetT8(TQuantDataT8s* pData);
	EQuantDataResult SetGtick(TQuantDataGtDataPoints* pData);
	EQuantDataResult Release();

private:
	bool IsValidProvider(const TQuantDataProviderSettings& provider);
	EQuantDataResult DownloadFromAlphaVantage(const TQuantDataDownloadSettings& settings);

	const TQuantDataAlloc m_alloc;
	const TQuantDataFree m_free;
	TQuantDataProviderSettings m_providerSettings;
};

} // namespace quantdata
