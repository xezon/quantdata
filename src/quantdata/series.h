
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <quantdata/provider.h>
#include <downloader.h>

namespace quantdata {

class CManager;

class CSeries : public IQuantDataSeries
{
private:
	using TDownloader = CDownloader<TStringAllocator>;

public:
	CSeries(CManager& manager, const TAllocatorFunctions& functions);

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
	CManager& m_manager;
	TAllocatorFunctions m_functions;
	TStringAllocator m_stringAllocator;
	SProvider m_provider;
};

} // namespace quantdata
