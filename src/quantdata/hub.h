
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
	using TInterface = IQuantDataHub;

private:
	using TQuantDataSymbolInfos = std::vector<TQuantDataSymbolInfo>;

	using TStaticPeriodArray = CArrayFunctions<CStaticArray<IQuantDataPeriods, TQuantDataPeriod>>;
	using TStaticSymbolArray = CArrayFunctions<CStaticArray<IQuantDataSymbols, TQuantDataSymbolInfo>>;
	using TNewSymbolArray    = CArrayFunctions<CNewArray   <IQuantDataSymbols, TQuantDataSymbolInfos, TSymbolInfos>>;

protected:
	CHub(const CManager& manager);

	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetPeriods(IQuantDataPeriods** ppPeriods);
	EQuantDataResult GetSymbols(IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings);
	EQuantDataResult DownloadOhlc(IQuantDataOhlc** ppOhlc, const TQuantDataDownloadSettings* pSettings);
	EQuantDataResult DownloadTick(IQuantDataTick** ppTick, const TQuantDataDownloadSettings* pSettings);
	EQuantDataResult LoadOhlc(IQuantDataOhlc** ppOhlc, const TQuantDataLoadSettings* pSettings);
	EQuantDataResult LoadTick(IQuantDataTick** ppTick, const TQuantDataLoadSettings* pSettings);
	EQuantDataResult Release();

private:
	EQuantDataResult ExtractJsonSymbols(const web::http::http_response& response, TSymbolInfos& symbolInfos);
	EQuantDataResult ExtractCsvSymbols(const web::http::http_response& response, TSymbolInfos& symbolInfos, const json::csv_parameters& csv);
	EQuantDataResult DownloadSymbols(const SProviderInfo& providerInfo, const size_t symbolListIndex, TSymbolInfos& symbolInfos);

	const CManager&  m_manager;
	SProvider        m_provider;
};

} // namespace quantdata
