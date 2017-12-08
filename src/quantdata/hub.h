
#pragma once

#include <quantdata/hub_functions.h>
#include <quantdata/types.h>
#include <quantdata/array_buf.h>
#include <quantdata/array_view.h>
#include <quantdata/ohlc.h>
#include <quantdata/tick.h>
#include <variant>

namespace quantdata {

class CManager;
struct SProviderInfo;

class CHub : public IQuantDataHub
{
protected:
	using TInterface = IQuantDataHub;

private:
	using TQuantDataSymbolInfos = std::vector<TQuantDataSymbolInfo>;

	using TPeriodArrayView = CArrayFunctions<CArrayView<IQuantDataPeriods, TQuantDataPeriod>>;
	using TSymbolArrayView = CArrayFunctions<CArrayView<IQuantDataSymbols, TQuantDataSymbolInfo>>;
	using TSymbolArrayBuf  = CArrayFunctions<CArrayBuf<IQuantDataSymbols, TQuantDataSymbolInfos, TSymbolInfos>>;
	using TOhlcBucket      = COhlcBucketFunctions<COhlcBucket>;

private:
	struct SOhlcResponse
	{
		TOhlcVector ohlcVector;
		CQuantDataPeriod period = CQuantDataPeriod::Day;
		EQuantDataTimezone timezone = EQuantDataTimezone::UTC;
	};

	struct IOhlcTasks
	{
		virtual EQuantDataResult BuildRequest(const TQuantDataDownloadSettings& settings, const SProviderSettings& provider, const SProviderInfo& providerInfo, http_request& request) = 0;
		virtual EQuantDataResult ParseResponse(const TQuantDataDownloadSettings& settings, const SProviderInfo& providerInfo, const http_response& response, SOhlcResponse& ohlcResponse) = 0;
	protected:
		~IOhlcTasks() {};
	};

	struct SOhlcTasksForAlphaVantage : public IOhlcTasks
	{
		virtual EQuantDataResult BuildRequest(const TQuantDataDownloadSettings& settings, const SProviderSettings& provider, const SProviderInfo& providerInfo, http_request& request) override;
		virtual EQuantDataResult ParseResponse(const TQuantDataDownloadSettings& settings, const SProviderInfo& providerInfo, const http_response& response, SOhlcResponse& ohlcResponse) override;
	};

	using TOhlcTasksVariant = std::variant<SOhlcTasksForAlphaVantage>;

protected:
	CHub(const CManager& manager);

	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetPeriods(IQuantDataPeriods** ppPeriods);
	EQuantDataResult GetSymbols(IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings);
	EQuantDataResult DownloadOhlc(IQuantDataOhlcBucket** ppOhlc, const TQuantDataDownloadSettings* pSettings);
	EQuantDataResult DownloadTick(IQuantDataTickBucket** ppTick, const TQuantDataDownloadSettings* pSettings);
	EQuantDataResult LoadOhlc(IQuantDataOhlcBucket** ppOhlc, const TQuantDataLoadSettings* pSettings);
	EQuantDataResult LoadTick(IQuantDataTickBucket** ppTick, const TQuantDataLoadSettings* pSettings);
	EQuantDataResult Release();

private:
	EQuantDataResult ExtractJsonSymbols(const http_response& response, TSymbolInfos& symbolInfos);
	EQuantDataResult ExtractCsvSymbols(const http_response& response, TSymbolInfos& symbolInfos, const json::csv_parameters& csv);
	EQuantDataResult DownloadSymbols(const SProviderInfo& providerInfo, const size_t symbolListIndex, TSymbolInfos& symbolInfos);
	static EQuantDataResult Download(http_client& client, const http_request& request, http_response& response);

	const CManager&   m_manager;
	SProviderSettings m_provider;
	IOhlcTasks*       m_pOhlcTasks;
	TOhlcTasksVariant m_ohlcTasksVariant;
};

} // namespace quantdata
