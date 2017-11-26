
#include <common/stl.h>
#include <quantdata/manager.h>
#include <quantdata/checks.h>
#include <quantdata/exceptions.h>
#include <common/util_log.h>
#include <cpprest/http_client.h>

// https://quant.stackexchange.com/questions/141/what-data-sources-are-available-online

#pragma warning(disable:4100 4189)

namespace quantdata {

template <class AllocatorFunctions>
CSeries<AllocatorFunctions>::CSeries(const TAllocatorFunctions& allocFunctions, const CManager& manager)
	: m_allocFunctions(allocFunctions)
	, m_manager(manager)
	, m_provider(allocFunctions)
{
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::SetProvider(const TQuantDataProviderSettings* pSettings)
{
	if (!IsValidProvider(pSettings))
		return EQuantDataResult::InvalidProvider;

	m_provider.Set(*pSettings);
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::GetNativePeriods(IQuantDataPeriods** ppPeriods)
{
	if (!ppPeriods)
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	const auto& providerInfo = m_manager.GetProviderInfo(m_provider.type);
	const auto pPeriods = mem::placement_alloc<TStaticPeriodArray>(m_allocFunctions.alloc(),
		m_allocFunctions, providerInfo.periods);
	*ppPeriods = pPeriods;
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::ExtractJsonSymbols(
	const web::http::http_response& response, TSymbolInfos& symbolInfos)
{
	try
	{
		const web::json::value& json = response.extract_json().get();
		return EQuantDataResult::Success;
	}
	catch (const web::http::http_exception& e)
	{
		return HandleHttpException(e);
	}
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::ExtractCsvSymbols(
	const web::http::http_response& response, TSymbolInfos& symbolInfos)
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::DownloadSymbols(
	const SProviderInfo& providerInfo, const size_t symbolListIndex, TSymbolInfos& symbolInfos)
{
	const TSymbolSources& symbolSources = providerInfo.symbolSources;
	if (symbolListIndex < symbolSources.size())
	{
		const TSymbolSource& symbolSource = symbolSources[symbolListIndex];
		web::http::client::http_client client(providerInfo.url);
		web::http::http_request request(web::http::methods::GET);
		request.set_request_uri(symbolSource.url);
		web::http::http_response response = client.request(request).get();

		if (response.status_code() == web::http::status_codes::OK)
		{
			switch (symbolSource.format)
			{
			case ETextFormat::json: return ExtractJsonSymbols(response, symbolInfos);
			case ETextFormat::csv: return ExtractCsvSymbols(response, symbolInfos);
			}
		}
		// TODO Handle error status
	}

	return EQuantDataResult::NoDataAvailable;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::GetSupportedSymbols(
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
		auto symbolBuffers = TNewSymbolArray::CreateBufferArray(m_allocFunctions);
		result = DownloadSymbols(providerInfo, symbolListIndex, symbolBuffers);

		if (result == EQuantDataResult::Success)
		{
			const size_t size = symbolBuffers.size();
			auto symbolElements = TNewSymbolArray::CreateElementArray(m_allocFunctions);
			symbolElements.resize(size);

			for (size_t i = 0; i < size; ++i)
			{
				symbolElements[i] = symbolBuffers[i].GetPod();
			}

			const auto pSymbols = mem::placement_alloc<TNewSymbolArray>(m_allocFunctions.alloc(),
				m_allocFunctions, std::move(symbolElements), std::move(symbolBuffers));
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
			const auto pSymbols = mem::placement_alloc<TStaticSymbolArray>(m_allocFunctions.alloc(),
				m_allocFunctions, symbols);
			*ppSymbols = pSymbols;
			return EQuantDataResult::Success;
		}
	}
	
	return result;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::Download(const TQuantDataDownloadSettings* pSettings)
{
	if (!IsValidDownload(pSettings))
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	// Download

	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::Load(const TQuantDataLoadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::Save(const TQuantDataSaveSettings* pSettings) const
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::GetT1(TQuantDataT1s** ppData) const
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::GetT2(TQuantDataT2s** ppData) const
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::GetT6(TQuantDataT6s** ppData) const
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::GetT8(TQuantDataT8s** ppData) const
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::GetGtick(TQuantDataGtDataPoints** ppData) const
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::SetT1(TQuantDataT1s* pData)
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::SetT2(TQuantDataT2s* pData)
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::SetT6(TQuantDataT6s* pData)
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::SetT8(TQuantDataT8s* pData)
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::SetGtick(TQuantDataGtDataPoints* pData)
{
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::Release()
{
	mem::placement_free(this, m_allocFunctions.free());
	return EQuantDataResult::Success;
}

} // namespace quantdata

#pragma warning(default:4100 4189)
