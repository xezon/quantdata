
#pragma once

#include <quantdata/series_functions.h>
#include <quantdata/downloader.h>
#include <quantdata/provider.h>
#include <quantdata/types.h>
#include <quantdata/array/new_array.h>
#include <quantdata/array/static_array.h>
#include <common/mem.h>

namespace quantdata {

class CManager;

template <class AllocatorFunctions>
using TPeriodArray = CArrayFunctions<CStaticArray<IQuantDataPeriods, AllocatorFunctions>>;

template <class AllocatorFunctions>
class CSeries : public IQuantDataSeries
{
protected:
	using TInterface          = IQuantDataSeries;
	using TAllocatorFunctions = AllocatorFunctions;

private:
	using TDownloader       = CDownloader<TAllocatorFunctions>;
	using TData             = typename TDownloader::TData;
	using TDataAllocator    = typename TDownloader::TDataAllocator;
	using TDownloadSettings = typename TDownloader::SDownloadSettings;
	using TDownloadInfo     = typename TDownloader::SDownloadInfo;
	using TPeriodArray      = TPeriodArray<TAllocatorFunctions>;
	using TStringA          = TString<char, TAllocatorFunctions>;
	using TStringAllocatorA = typename TStringA::allocator_type;

protected:
	CSeries(const CManager& manager, const TAllocatorFunctions& allocFunctions);

	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetNativePeriods(IQuantDataPeriods** ppPeriods);
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
	const CManager&                m_manager;
	const TAllocatorFunctions      m_allocFunctions;
	SProvider<TAllocatorFunctions> m_provider;
};

} // namespace quantdata

#include <quantdata/series_impl.h>
