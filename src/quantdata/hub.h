
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

	struct IProviderJobs
	{
		virtual EQuantDataResult BuildOhlcRequest(const TQuantDataDownloadSettings& settings, const SProviderSettings& provider,
			const SProviderInfo& providerInfo, http_request& request) const = 0;
		virtual EQuantDataResult ParseOhlcResponse(const TQuantDataDownloadSettings& settings, const SProviderInfo& providerInfo,
			const http_response& response, SOhlcResponse& ohlcResponse) const = 0;
	protected:
		~IProviderJobs() {};
	};

	struct SAlphaVantageJobs : public IProviderJobs
	{
		virtual EQuantDataResult BuildOhlcRequest(const TQuantDataDownloadSettings& settings, const SProviderSettings& provider,
			const SProviderInfo& providerInfo, http_request& request) const override;
		virtual EQuantDataResult ParseOhlcResponse(const TQuantDataDownloadSettings& settings, const SProviderInfo& providerInfo,
			const http_response& response, SOhlcResponse& ohlcResponse) const override;
	};

	using TProviderJobsVariant = std::variant<SAlphaVantageJobs>;

protected:
	CHub(const CManager& manager);

	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetPeriods(IQuantDataPeriods** ppPeriods) const;
	EQuantDataResult GetSymbols(IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings) const;
	EQuantDataResult DownloadOhlc(IQuantDataOhlcBucket** ppOhlc, const TQuantDataDownloadSettings* pSettings) const;
	EQuantDataResult DownloadTick(IQuantDataTickBucket** ppTick, const TQuantDataDownloadSettings* pSettings) const;
	EQuantDataResult LoadOhlc(IQuantDataOhlcBucket** ppOhlc, const TQuantDataLoadSettings* pSettings) const;
	EQuantDataResult LoadTick(IQuantDataTickBucket** ppTick, const TQuantDataLoadSettings* pSettings) const;
	void             Release();

private:
	EQuantDataResult ExtractJsonSymbols(const http_response& response, TSymbolInfos& symbolInfos) const;
	EQuantDataResult ExtractCsvSymbols(const http_response& response, TSymbolInfos& symbolInfos, const json::csv_parameters& csv) const;
	EQuantDataResult DownloadSymbols(const SProviderInfo& providerInfo, const size_t symbolListIndex, TSymbolInfos& symbolInfos) const;
	static EQuantDataResult Download(http_client& client, const http_request& request, http_response& response);

	const CManager&      m_manager;
	SProviderSettings    m_provider;
	IProviderJobs*       m_pJobs;
	TProviderJobsVariant m_jobs;
};

} // namespace quantdata
