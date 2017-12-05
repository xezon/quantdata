
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <quantdata/api.h>

namespace quantdata {

using TStringT            = internal::TStringT;
using TPeriods            = internal::TPeriods;
using ESymbolSourceFormat = internal::ESymbolSourceFormat;
using ESymbolSourceFlags  = internal::ESymbolSourceFlags;
using SSymbolSource       = internal::SSymbolSource;
using TSymbolSources      = internal::TSymbolSources;
using TSymbols            = internal::TSymbols;
using TSymbolsList        = internal::TSymbolsList;

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

	EQuantDataResult SetAllocator(const TQuantDataAllocatorSettings* pSettings);
	EQuantDataResult CreateHub(IQuantDataHub** ppHub);

	inline const SProviderInfo& GetProviderInfo(CQuantDataProvider provider) const
	{
		return m_providerInfos[provider.ordinal()];
	}

private:	
	TProviderInfos m_providerInfos;
	bool m_allocatorInUse = false;
};

} // namespace quantdata
