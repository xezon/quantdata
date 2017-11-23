
#include <common/stl.h>
#include <quantdata/manager.h>
#include <quantdata/checks.h>
#include <common/util_log.h>

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
	const auto& pPeriods = mem::placement_alloc<TStaticPeriodArray>(m_allocFunctions.alloc(),
		m_allocFunctions, providerInfo.periods);
	*ppPeriods = pPeriods;
	return EQuantDataResult::Success;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::GetSupportedSymbols(IQuantDataSymbols** ppSymbols, const TQuantDataSymbolSettings* pSettings)
{
	if (!ppSymbols || !pSettings)
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	const auto& providerInfo = m_manager.GetProviderInfo(m_provider.type);

	if (pSettings->download)
	{
		const auto& symbolSources = providerInfo.symbolSources;
		if (!symbolSources.empty())
		{

			// sample

			const auto& nativeSymbols = providerInfo.nativeSymbolsArray.at(0);
			auto symbols = TNewSymbolArray::CreateBuffers(m_allocFunctions);
			auto symbolLinks = TNewSymbolArray::CreateElements(m_allocFunctions);
			const size_t size = nativeSymbols.size();
			symbols.resize(size, m_allocFunctions);
			symbolLinks.resize(size);

			for (size_t i = 0; i < size; ++i)
			{
				symbols[i].Set(nativeSymbols[i]);
				symbolLinks[i] = symbols[i].GetPod();
			}
			const auto& pSymbols = mem::placement_alloc<TNewSymbolArray>(m_allocFunctions.alloc(),
				m_allocFunctions, std::move(symbolLinks), std::move(symbols));
			*ppSymbols = pSymbols;

			return EQuantDataResult::Success;
		}
	}
	else
	{
		const auto& nativeSymbolsArray = providerInfo.nativeSymbolsArray;
		if (pSettings->index < nativeSymbolsArray.size())
		{
			const auto& nativeSymbols = nativeSymbolsArray.at(pSettings->index);
			const auto& pSymbols = mem::placement_alloc<TStaticSymbolArray>(m_allocFunctions.alloc(),
				m_allocFunctions, nativeSymbols);
			*ppSymbols = pSymbols;

			return EQuantDataResult::Success;
		}
	}
	
	return EQuantDataResult::NoDataAvailable;
}

template <class AllocatorFunctions>
EQuantDataResult CSeries<AllocatorFunctions>::Download(const TQuantDataDownloadSettings* pSettings)
{
	if (!IsValidDownload(pSettings))
		return EQuantDataResult::InvalidArgument;

	if (!m_manager.IsInitialized())
		return EQuantDataResult::NotInitialized;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	auto header     = TStringA(TStringAllocatorA(m_allocFunctions));
	auto page       = TStringA(TStringAllocatorA(m_allocFunctions));
	auto dlsettings = CDownloader::SDownloadSettings<TStringA>();
	auto dlinfo     = CDownloader::SDownloadInfo();

	auto url = stl::string_format_t<TStringA>(TStringAllocatorA(m_allocFunctions),
		"https://www.alphavantage.co/"
		"query?function=TIME_SERIES_INTRADAY"
		"&symbol=%s&interval=1min&apikey=demo&datatype=csv", pSettings->symbol);

	util::clog("Downloading '%s'", url.c_str());

	dlsettings.url = url;
	dlsettings.certtype = m_provider.certtype;
	dlsettings.certfile = m_provider.certfile;
	CURLcode code = CDownloader::Download(dlsettings, &header, &page, &dlinfo);

	if (code != CURLE_OK)
	{
		util::cerr("Download error '%d' : '%s'", static_cast<int>(code), CDownloader::GetErrorString(code));
	}

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
