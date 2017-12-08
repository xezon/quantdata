
#include <quantdata/hub.h>
#include <quantdata/manager.h>
#include <quantdata/checks.h>
#include <quantdata/exceptions.h>
#include <common/stl.h>
#include <common/util_log.h>

// https://quant.stackexchange.com/questions/141/what-data-sources-are-available-online

#pragma warning(push)
#pragma warning(disable : 4100 4189)

namespace quantdata {


CHub::CHub(const CManager& manager)
	: m_manager(manager)
	, m_pOhlcTasks(nullptr)
{
}

EQuantDataResult CHub::SetProvider(const TQuantDataProviderSettings* pSettings)
{
	if (IsValidProvider(pSettings))
	{
		m_provider.Set(*pSettings);

		switch (m_provider.type)
		{
		case EQuantDataProvider::AlphaVantage:
			m_pOhlcTasks = &m_ohlcTasksVariant.emplace<SOhlcTasksForAlphaVantage>();
			break;
		default:
			m_pOhlcTasks = nullptr;
			break;
		}

		return EQuantDataResult::Success;
	}

	m_provider.Reset();
	m_pOhlcTasks = nullptr;
	return EQuantDataResult::InvalidProvider;
}

EQuantDataResult CHub::GetPeriods(IQuantDataPeriods** ppPeriods)
{
	if (!ppPeriods)
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	const auto& providerInfo = m_manager.GetProviderInfo(m_provider.type);
	const auto pPeriods = mem::placement_g_alloc<TStaticPeriodArray>(providerInfo.supportedPeriods);
	*ppPeriods = pPeriods;
	return EQuantDataResult::Success;
}

EQuantDataResult CHub::ExtractJsonSymbols(
	const http_response& response,
	TSymbolInfos& symbolInfos)
{
	std::string utf8string;

	try
	{
		utf8string = response.extract_utf8string(false).get();
	}
	catch (const http_exception& e)
	{
		return HandleException(e);
	}

	try
	{
		json::json json = json::json::parse(utf8string);
		stl::clear_mem(utf8string);
		const size_t size = json.size();
		symbolInfos.resize(size);

		size_t index = 0;
		for (const auto& obj : json.object_range())
		{
			SSymbolInfo& symbolInfo = symbolInfos[index++];
			symbolInfo.name = obj.key();
			symbolInfo.desc = obj.value().as_string();
		}
	}
	catch (const json::json_exception& e)
	{
		return HandleException(e);
	}

	return EQuantDataResult::Success;
}

EQuantDataResult CHub::ExtractCsvSymbols(
	const http_response& response,
	TSymbolInfos& symbolInfos,
	const json::csv_parameters& csv)
{
	std::string utf8string;

	try
	{
		utf8string = response.extract_utf8string(true).get();
	}
	catch (const http_exception& e)
	{
		return HandleException(e);
	}

	try
	{
		json::json json = jsoncons::csv::decode_csv<json::json>(utf8string, csv);
		stl::clear_mem(utf8string);
		symbolInfos = json.as<TSymbolInfos>();
	}
	catch (const json::json_exception& e)
	{
		return HandleException(e);
	}

	return EQuantDataResult::Success;
}

EQuantDataResult CHub::DownloadSymbols(
	const SProviderInfo& providerInfo,
	const size_t symbolListIndex,
	TSymbolInfos& symbolInfos)
{
	const TSymbolSources& symbolSources = providerInfo.symbolSources;
	if (symbolListIndex < symbolSources.size())
	{
		const SSymbolSource& symbolSource = symbolSources[symbolListIndex];
		http_client client(providerInfo.url);
		http_request request(http_methods::GET);
		request.set_request_uri(symbolSource.query);
		http_response response;
		
		EQuantDataResult result = Download(client, request, response);

		if (result == EQuantDataResult::Success)
		{
			switch (symbolSource.format)
			{
			case ESymbolSourceFormat::json: return ExtractJsonSymbols(response, symbolInfos);
			case ESymbolSourceFormat::csv: return ExtractCsvSymbols(response, symbolInfos, symbolSource.csv);
			}
		}
	}

	return EQuantDataResult::NoDataAvailable;
}

EQuantDataResult CHub::GetSymbols(
	IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings)
{
	if (!ppSymbols || !pSettings)
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	EQuantDataResult result = EQuantDataResult::NoDataAvailable;
	const SProviderInfo& providerInfo = m_manager.GetProviderInfo(m_provider.type);
	const size_t symbolListIndex = static_cast<size_t>(pSettings->index);

	if (pSettings->download)
	{
		typename TNewSymbolArray::TBuffers symbolBuffers;
		result = DownloadSymbols(providerInfo, symbolListIndex, symbolBuffers);

		if (result == EQuantDataResult::Success)
		{
			const size_t size = symbolBuffers.size();
			typename TNewSymbolArray::TElements symbolElements;
			symbolElements.resize(size);

			for (size_t i = 0; i < size; ++i)
			{
				symbolElements[i] = symbolBuffers[i].GetPod();
			}

			const auto pSymbols = mem::placement_g_alloc<TNewSymbolArray>(
				std::move(symbolElements), std::move(symbolBuffers));
			*ppSymbols = pSymbols;
			return EQuantDataResult::Success;
		}
	}
	else
	{
		const auto& symbolsList = providerInfo.symbolsList;
		if (symbolListIndex < symbolsList.size())
		{
			const TSymbols& symbols = symbolsList.at(symbolListIndex);
			const auto pSymbols = mem::placement_g_alloc<TStaticSymbolArray>(symbols);
			*ppSymbols = pSymbols;
			return EQuantDataResult::Success;
		}
	}
	
	return result;
}

EQuantDataResult CHub::DownloadOhlc(IQuantDataOhlcBucket** ppOhlc, const TQuantDataDownloadSettings* pSettings)
{
	if (!ppOhlc || !IsValidDownload(pSettings))
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	if (!m_pOhlcTasks)
		return EQuantDataResult::UnsupportedFeature;
	
	CQuantDataPeriod period(pSettings->period);

	if (!period.is_valid())
		return EQuantDataResult::UnsupportedPeriod;

	const CQuantDataProvider& provider = m_provider.type;
	const SProviderInfo& providerInfo = m_manager.GetProviderInfo(provider);
	http_request request;
	EQuantDataResult result = m_pOhlcTasks->BuildRequest(*pSettings, m_provider, providerInfo, request);

	if (result == EQuantDataResult::Success)
	{
		http_client client(providerInfo.url);
		http_response response;

		result = Download(client, request, response);

		if (result == EQuantDataResult::Success)
		{
			SOhlcResponse ohlcResponse;
			ohlcResponse.period = period;

			result = m_pOhlcTasks->ParseResponse(*pSettings, providerInfo, response, ohlcResponse);

			if (result == EQuantDataResult::Success)
			{
				*ppOhlc = mem::placement_g_alloc<TOhlcBucket>(
					std::move(ohlcResponse.ohlcVector), provider,
					ohlcResponse.period, ohlcResponse.timezone);
			}
		}
	}

	return result;
}

EQuantDataResult CHub::SOhlcTasksForAlphaVantage::BuildRequest(
	const TQuantDataDownloadSettings& settings,
	const SProvider& provider,
	const SProviderInfo& providerInfo,
	http_request& request)
{
	const CQuantDataPeriod period(settings.period);
	const http_string wapikey = to_web_string(provider.apikey);
	const http_string wsymbol = to_web_string(util::get_valid_string(settings.symbol));
	const http_string wmarket = to_web_string(util::get_valid_string(settings.market));
	const http_string winterval = providerInfo.periodNames[period.ordinal()];

	const bool requestCrypto = !wmarket.empty();
	uri_builder uri_builder;
	uri_builder.append_path(U("query"));

	if (requestCrypto)
	{
		if (settings.adjusted)
		{
			return EQuantDataResult::UnsupportedAdjustment;
		}
		else
		{
			if (period.equals(CQuantDataPeriod::Day))
			{
				uri_builder.append_query(U("function"), U("DIGITAL_CURRENCY_DAILY"));
			}
			else if (period.equals(CQuantDataPeriod::Week))
			{
				uri_builder.append_query(U("function"), U("DIGITAL_CURRENCY_WEEKLY"));
			}
			else if (period.equals(CQuantDataPeriod::Month))
			{
				uri_builder.append_query(U("function"), U("DIGITAL_CURRENCY_MONTHLY"));
			}
			else
			{
				return EQuantDataResult::UnsupportedPeriod;
			}
		}
	}
	else
	{
		if (settings.adjusted)
		{
			if (period.equals(CQuantDataPeriod::Day))
			{
				uri_builder.append_query(U("function"), U("TIME_SERIES_DAILY_ADJUSTED"));
			}
			else if (period.equals(CQuantDataPeriod::Week))
			{
				uri_builder.append_query(U("function"), U("TIME_SERIES_WEEKLY_ADJUSTED"));
			}
			else if (period.equals(CQuantDataPeriod::Month))
			{
				uri_builder.append_query(U("function"), U("TIME_SERIES_MONTHLY_ADJUSTED"));
			}
			else
			{
				return EQuantDataResult::UnsupportedAdjustment;
			}
		}
		else
		{
			if (period.equals(CQuantDataPeriod::Day))
			{
				uri_builder.append_query(U("function"), U("TIME_SERIES_DAILY"));
			}
			else if (period.equals(CQuantDataPeriod::Week))
			{
				uri_builder.append_query(U("function"), U("TIME_SERIES_WEEKLY"));
			}
			else if (period.equals(CQuantDataPeriod::Month))
			{
				uri_builder.append_query(U("function"), U("TIME_SERIES_MONTHLY"));
			}
			else
			{
				uri_builder.append_query(U("function"), U("TIME_SERIES_INTRADAY"));
			}
		}
	}

	uri_builder.append_query(U("symbol"), wsymbol);

	if (requestCrypto)
	{
		uri_builder.append_query(U("market"), wmarket);
	}
	if (!requestCrypto && winterval != UnnamedPeriod)
	{
		uri_builder.append_query(U("interval"), winterval);
	}
	uri_builder.append_query(U("apikey"), wapikey);
	uri_builder.append_query(U("datatype"), U("json"));
	uri uri = uri_builder.to_uri();
	request.set_request_uri(uri);
	request.set_method(http_methods::GET);

	return EQuantDataResult::Success;
}

EQuantDataResult CHub::SOhlcTasksForAlphaVantage::ParseResponse(
	const TQuantDataDownloadSettings& settings,
	const SProviderInfo& providerInfo,
	const http_response& response,
	SOhlcResponse& ohlcResponse)
{
	std::string utf8string;

	try
	{
		utf8string = response.extract_utf8string(false).get();
	}
	catch (const http_exception& e)
	{
		return HandleException(e);
	}

	try
	{
		const json::json jsonBase = json::json::parse(utf8string);
		stl::clear_mem(utf8string);

		const json::json jsonMeta = jsonBase.at(0);
		const json::json jsonData = jsonBase.at(1);
		
		const json::const_json_object_iterator pTimezone = json::find_similar(jsonMeta, "Time Zone");
		const json::const_json_object_iterator pMetaEnd = jsonMeta.object_range().end();

		if (pTimezone != pMetaEnd)
		{
			const string& timezoneName = pTimezone->value().as_string();

			if (timezoneName == "US/Eastern")
			{
				ohlcResponse.timezone = EQuantDataTimezone::EST;
			}
			else if (timezoneName == "UTC")
			{
				ohlcResponse.timezone = EQuantDataTimezone::UTC;
			}
			else
			{
				return EQuantDataResult::UnrecognizedTimezone;
			}
		}

		const size_t size = jsonData.size();
		TOhlcVector& ohlcVector = ohlcResponse.ohlcVector;
		ohlcVector.reserve(size);

		for (auto pair : jsonData.object_range())
		{
			const string_view datetimeString = pair.key();
			istringstream datetimeStream(datetimeString.data(), datetimeString.size());
			date::sys_seconds seconds;
			date::from_stream(datetimeStream, "%Y-%m-%d %H:%M:%S", seconds);

			// AlphaVantage returns multiple ohlc entries for crypto currencies.
			// The first one is for the user specified market symbol, and the second for USD.
			// This code will just return ohlc for the market symbol and discard the USD data.

			const json::json jsonOhlc = pair.value();
			const json::const_json_object_iterator pOpen    = json::find_similar(jsonOhlc, "open");
			const json::const_json_object_iterator pHigh    = json::find_similar(jsonOhlc, "high");
			const json::const_json_object_iterator pLow     = json::find_similar(jsonOhlc, "low");
			const json::const_json_object_iterator pClose   = json::find_similar(jsonOhlc, "close");
			const json::const_json_object_iterator pVolume  = json::find_similar(jsonOhlc, "volume");
			const json::const_json_object_iterator pOhlcEnd = jsonOhlc.object_range().end();

			if (pOpen == pOhlcEnd || pHigh == pOhlcEnd || pLow == pOhlcEnd || pClose == pOhlcEnd || pVolume == pOhlcEnd)
			{
				return EQuantDataResult::MalformedData;
			}

			SQuantDataOhlc ohlc;
			ohlc.time   = seconds.time_since_epoch().count();
			ohlc.open   = pOpen->value().as_double();
			ohlc.high   = pHigh->value().as_double();
			ohlc.low    = pLow->value().as_double();
			ohlc.close  = pClose->value().as_double();
			ohlc.volume = pVolume->value().as_double();
			
			ohlcVector.emplace_back(std::move(ohlc));
		}
	}
	catch (const json::json_exception& e)
	{
		return HandleException(e);
	}

	return EQuantDataResult::Success;
}

EQuantDataResult CHub::DownloadTick(IQuantDataTickBucket** ppTick, const TQuantDataDownloadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CHub::LoadOhlc(IQuantDataOhlcBucket** ppOhlc, const TQuantDataLoadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CHub::LoadTick(IQuantDataTickBucket** ppTick, const TQuantDataLoadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CHub::Release()
{
	mem::placement_g_free(this);
	return EQuantDataResult::Success;
}

EQuantDataResult CHub::Download(http_client& client, const http_request& request, http_response& response)
{
	try
	{
		response = client.request(request).get();
	}
	catch (const http_exception& e)
	{
		return HandleException(e);
	}

	status_code code = response.status_code();

	if (code != status_codes::OK)
	{
		return static_cast<EQuantDataResult>(code);
	}

	return EQuantDataResult::Success;
}

} // namespace quantdata

#pragma warning(pop)
