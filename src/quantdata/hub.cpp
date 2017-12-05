
#include <quantdata/hub.h>
#include <quantdata/manager.h>
#include <quantdata/checks.h>
#include <quantdata/exceptions.h>
#include <common/stl.h>
#include <common/util_log.h>
#include <common/utf8.h>
#include <cpprest/http_client.h>

// https://quant.stackexchange.com/questions/141/what-data-sources-are-available-online

#pragma warning(push)
#pragma warning(disable : 4100 4189)

namespace quantdata {


CHub::CHub(const CManager& manager)
	: m_manager(manager)
{
}

EQuantDataResult CHub::SetProvider(const TQuantDataProviderSettings* pSettings)
{
	if (IsValidProvider(pSettings))
	{
		m_provider.Set(*pSettings);
		return EQuantDataResult::Success;
	}

	m_provider.Reset();
	return EQuantDataResult::InvalidProvider;
}

EQuantDataResult CHub::GetPeriods(IQuantDataPeriods** ppPeriods)
{
	if (!ppPeriods)
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	const auto& providerInfo = m_manager.GetProviderInfo(m_provider.type);
	const auto pPeriods = mem::placement_g_alloc<TStaticPeriodArray>(providerInfo.periods);
	*ppPeriods = pPeriods;
	return EQuantDataResult::Success;
}

EQuantDataResult CHub::ExtractJsonSymbols(
	const web::http::http_response& response,
	TSymbolInfos& symbolInfos)
{
	std::string utf8string;

	try
	{
		utf8string = response.extract_utf8string(false).get();
	}
	catch (const web::http::http_exception& e)
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
	const web::http::http_response& response,
	TSymbolInfos& symbolInfos,
	const json::csv_parameters& csv)
{
	std::string utf8string;

	try
	{
		utf8string = response.extract_utf8string(true).get();
	}
	catch (const web::http::http_exception& e)
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
		web::http::client::http_client client(providerInfo.url);
		web::http::http_request request(web::http::methods::GET);
		request.set_request_uri(symbolSource.query);
		web::http::http_response response;
		
		try
		{
			response = client.request(request).get();
		}
		catch (const web::http::http_exception& e)
		{
			return HandleException(e);
		}
		
		web::http::status_code code = response.status_code();

		if (code == web::http::status_codes::OK)
		{
			switch (symbolSource.format)
			{
			case ESymbolSourceFormat::json: return ExtractJsonSymbols(response, symbolInfos);
			case ESymbolSourceFormat::csv: return ExtractCsvSymbols(response, symbolInfos, symbolSource.csv);
			}
		}

		return static_cast<EQuantDataResult>(code);
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

EQuantDataResult CHub::DownloadOhlc(IQuantDataOhlc** ppOhlc, const TQuantDataDownloadSettings* pSettings)
{
	if (!IsValidDownload(pSettings))
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	// Download

	return EQuantDataResult::Success;
}

EQuantDataResult CHub::DownloadTick(IQuantDataTick** ppTick, const TQuantDataDownloadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CHub::LoadOhlc(IQuantDataOhlc** ppOhlc, const TQuantDataLoadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CHub::LoadTick(IQuantDataTick** ppTick, const TQuantDataLoadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CHub::Release()
{
	mem::placement_g_free(this);
	return EQuantDataResult::Success;
}

} // namespace quantdata

#pragma warning(pop)
