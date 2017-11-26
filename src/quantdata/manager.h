
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <quantdata/api.h>

namespace quantdata {

using TStringT       = internal::TStringT;
using TPeriods       = internal::TPeriods;
using TSymbolSource  = internal::SSymbolSource;
using TSymbolSources = internal::TSymbolSources;
using TSymbols       = internal::TSymbols;
using TSymbolsList   = internal::TSymbolsList;
using ETextFormat    = internal::ETextFormat;

struct SProviderInfo
{
	TStringT       url;
	TPeriods       periods;
	TSymbolSources symbolSources;
	TSymbolsList   symbolsList;
};

class CManager
{
private:
	using TProviderInfos = std::array<SProviderInfo, CQuantDataProvider::count()>;

public:
	CManager();

	EQuantDataResult CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings);

	inline const SProviderInfo& GetProviderInfo(CQuantDataProvider provider) const
	{
		return m_providerInfos[provider.ordinal()];
	}

private:	
	TProviderInfos m_providerInfos;
};

} // namespace quantdata
