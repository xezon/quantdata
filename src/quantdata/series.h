
#pragma once

#include <quantdata/series_functions.h>
#include <quantdata/structs.h>
#include <quantdata/types.h>
#include <quantdata/array/new_array.h>
#include <quantdata/array/static_array.h>
#include <common/mem.h>
#include <vector>

namespace web {
namespace http {
class http_response;
}
}

namespace quantdata {

class CManager;

template <class AllocatorFunctions>
class CSeries : public IQuantDataSeries
{
protected:
	using TInterface          = IQuantDataSeries;
	using TAllocatorFunctions = AllocatorFunctions;

private:
	using TProvider           = SProvider<TAllocatorFunctions>;
	using TStringA            = TStringA<TAllocatorFunctions>;
	using TStringAllocatorA   = TStringAllocatorA<TAllocatorFunctions>;
	using TSymbolInfo         = SSymbolInfo<TAllocatorFunctions>;
	using TSymbolInfos        = TVector<TSymbolInfo, TAllocatorFunctions>;

	using TStaticPeriodArray  = CArrayFunctions<CStaticArray<IQuantDataPeriods, TAllocatorFunctions, TQuantDataPeriod>>;
	using TStaticSymbolArray  = CArrayFunctions<CStaticArray<IQuantDataSymbols, TAllocatorFunctions, TQuantDataSymbolInfo>>;
	using TNewSymbolArray     = CArrayFunctions<CNewArray   <IQuantDataSymbols, TAllocatorFunctions, TQuantDataSymbolInfo, TSymbolInfo>>;

protected:
	CSeries(const TAllocatorFunctions& allocFunctions, const CManager& manager);

	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetNativePeriods(IQuantDataPeriods** ppPeriods);
	EQuantDataResult GetSupportedSymbols(IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings);
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
	static EQuantDataResult ExtractJsonSymbols(const web::http::http_response& response, TSymbolInfos& symbolInfos);
	static EQuantDataResult ExtractCsvSymbols(const web::http::http_response& response, TSymbolInfos& symbolInfos);
	static EQuantDataResult DownloadSymbols(const SProviderInfo& providerInfo, const size_t symbolListIndex, TSymbolInfos& symbolInfos);

	const TAllocatorFunctions m_allocFunctions;
	const CManager&           m_manager;
	TProvider                 m_provider;
};

} // namespace quantdata

#include <quantdata/series_impl.h>
