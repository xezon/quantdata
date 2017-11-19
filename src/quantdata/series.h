
#pragma once

#include <quantdata/series_functions.h>
#include <quantdata/provider.h>
#include <quantdata/array/new_array.h>
#include <quantdata/array/static_array.h>
#include <downloader.h>
#include <vector>

namespace quantdata {

class CManager;

template <class AllocatorFunctions>
using TPeriodArray = CArrayFunctions<CStaticArray<IQuantDataPeriods, AllocatorFunctions>>;

class CSeries : public IQuantDataSeries
{
protected:
	using TInterface = IQuantDataSeries;

private:
	using TDownloader   = CDownloader<TCustomAllocator<char>>;
	using TPeriodArray  = TPeriodArray<TAllocatorFunctions>;

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
	const CManager&              m_manager;
	const TAllocatorFunctions    m_allocFunctions;
	const TCustomAllocator<char> m_stringAllocator;
	SProvider                    m_provider;
};

} // namespace quantdata
