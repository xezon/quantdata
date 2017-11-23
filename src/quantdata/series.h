
#pragma once

#include <quantdata/series_functions.h>
#include <quantdata/downloader.h>
#include <quantdata/structs.h>
#include <quantdata/types.h>
#include <quantdata/array/new_array.h>
#include <quantdata/array/static_array.h>
#include <common/mem.h>

namespace quantdata {

class CManager;

template <class AllocatorFunctions>
class CSeries : public IQuantDataSeries
{
protected:
	using TInterface          = IQuantDataSeries;
	using TAllocatorFunctions = AllocatorFunctions;

private:
	using TStringA            = TStringA<TAllocatorFunctions>;
	using TStringAllocatorA   = TStringAllocatorA<TAllocatorFunctions>;

	using TStaticPeriodArray  = CArrayFunctions<CStaticArray<IQuantDataPeriods, TAllocatorFunctions, TQuantDataPeriod>>;
	using TStaticSymbolArray  = CArrayFunctions<CStaticArray<IQuantDataSymbols, TAllocatorFunctions, TQuantDataSymbolInfo>>;
	using TNewSymbolArray     = CArrayFunctions<CNewArray   <IQuantDataSymbols, TAllocatorFunctions, TQuantDataSymbolInfo, SSymbolInfo<TAllocatorFunctions>>>;

protected:
	CSeries(const TAllocatorFunctions& allocFunctions, const CManager& manager);

	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetNativePeriods(IQuantDataPeriods** ppPeriods);
	EQuantDataResult GetSupportedSymbols(IQuantDataSymbols** ppSymbols, const TQuantDataSymbolSettings* pSettings);
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
	const TAllocatorFunctions      m_allocFunctions;
	const CManager&                m_manager;
	SProvider<TAllocatorFunctions> m_provider;
};

} // namespace quantdata

#include <quantdata/series_impl.h>
