
#pragma once

#include <quantdata/hub_functions.h>
#include <quantdata/structs.h>
#include <quantdata/types.h>
#include <quantdata/array/new_array.h>
#include <quantdata/array/static_array.h>

namespace web {
namespace http {
class http_response;
}
}

namespace quantdata {

class CManager;
struct SProviderInfo;

class CHub : public IQuantDataHub
{
protected:
	using TInterface          = IQuantDataHub;

private:
	using TStaticPeriodArray  = CArrayFunctions<CStaticArray<IQuantDataPeriods, TQuantDataPeriod>>;
	using TStaticSymbolArray  = CArrayFunctions<CStaticArray<IQuantDataSymbols, TQuantDataSymbolInfo>>;
	using TNewSymbolArray     = CArrayFunctions<CNewArray   <IQuantDataSymbols, TQuantDataSymbolInfo, SSymbolInfo>>;

protected:
	CHub(const CManager& manager);

	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetPeriods(IQuantDataPeriods** ppPeriods);
	EQuantDataResult GetSymbols(IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings);
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
	EQuantDataResult ExtractJsonSymbols(const web::http::http_response& response, TSymbolInfos& symbolInfos);
	EQuantDataResult ExtractCsvSymbols(const web::http::http_response& response, TSymbolInfos& symbolInfos);
	EQuantDataResult DownloadSymbols(const SProviderInfo& providerInfo, const size_t symbolListIndex, TSymbolInfos& symbolInfos);

	const CManager&  m_manager;
	SProvider        m_provider;
};

} // namespace quantdata
