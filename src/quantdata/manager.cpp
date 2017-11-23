
#include "manager.h"
#include <quantdata/series.h>
#include <common/util.h>
#include <algorithm>

namespace quantdata {

template <class AllocatorFunctions>
using TSeries = CSeriesFunctions<CSeries<AllocatorFunctions>>;

CManager::CManager()
{
	BuildSymbolSources();
	BuildNativeSymbols();
	BuildPeriods();
}

template <class Type, size_t Size>
void CManager::BuildSymbolSourcesFor(const CQuantDataProvider& provider, const Type(&sources)[Size])
{
	auto& providerInfo = m_providerInfos[provider.ordinal()];
	auto& symbolSources = providerInfo.symbolSources;
	symbolSources.resize(Size);
	std::copy(sources, sources + Size, symbolSources.begin());
}

void CManager::BuildSymbolSources()
{
	BuildSymbolSourcesFor(CQuantDataProvider::Oanda       , internal::oandaSymbolSources);
	BuildSymbolSourcesFor(CQuantDataProvider::AlphaVantage, internal::alphaVantageSymbolSources);
	BuildSymbolSourcesFor(CQuantDataProvider::OpenExchange, internal::openExchangeSymbolSources);
}

template <class Type, size_t Size>
void CManager::BuildNativeSymbolsFor(const CQuantDataProvider& provider, const Type(&symbols)[Size])
{
	auto& providerInfo = m_providerInfos[provider.ordinal()];
	auto& nativeSymbols = providerInfo.nativeSymbolsArray;
	nativeSymbols.emplace_back();
	auto& newSymbols = nativeSymbols.back();
	newSymbols.resize(Size);
	std::copy(symbols, symbols + Size, newSymbols.begin());
}

void CManager::BuildNativeSymbols()
{
	BuildNativeSymbolsFor(CQuantDataProvider::AlphaVantage, internal::alphaVantageDigitalCurrencies);
	BuildNativeSymbolsFor(CQuantDataProvider::AlphaVantage, internal::alphaVantagePhysicalCurrencies);
	BuildNativeSymbolsFor(CQuantDataProvider::OpenExchange, internal::openExchangeSymbols);
	BuildNativeSymbolsFor(CQuantDataProvider::TrueFx      , internal::trueFxSymbols);
}

void CManager::BuildPeriods()
{
	for (CQuantDataProvider provider : CQuantDataProvider())
	{
		const auto ordinal = provider.ordinal();
		auto& providerInfo = m_providerInfos[ordinal];

		for (CQuantDataPeriod period : CQuantDataPeriod())
		{
			const auto apiName = period.meta().apiNames[ordinal];
			if (util::is_valid_string(apiName))
			{
				const auto value = period.value();
				providerInfo.periods.push_back(value);
			}
		}
	}
}

EQuantDataResult CManager::Init()
{
	if (!m_isInitialized)
	{
		if (curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK)
		{
			m_isInitialized = true;
			return EQuantDataResult::Success;
		}
	}
	return EQuantDataResult::Failure;
}

EQuantDataResult CManager::Shutdown()
{
	if (m_isInitialized)
	{
		curl_global_cleanup();
		m_isInitialized = false;
		return EQuantDataResult::Success;
	}
	return EQuantDataResult::Failure;
}

EQuantDataResult CManager::CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings)
{
	if (!m_isInitialized)
		return EQuantDataResult::NotInitialized;

	if (!ppSeries || !pSettings)
		return EQuantDataResult::InvalidArgument;

	const auto alloc = pSettings->alloc;
	const auto free = pSettings->free;

	if (alloc && free)
	{
		const auto functions = mem::custom_allocator_functions(alloc, free);
		*ppSeries = mem::placement_alloc<TSeries<decltype(functions)>>(functions.alloc(), functions, *this);
	}
	else
	{
		const auto functions = mem::regular_allocator_functions();
		*ppSeries = mem::placement_alloc<TSeries<decltype(functions)>>(functions.alloc(), functions, *this);
	}

	return EQuantDataResult::Success;
}

} // namespace quantdata
