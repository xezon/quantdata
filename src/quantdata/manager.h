
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <quantdata/symbols.h>
#include <vector>
#include <array>
#include <string_view>

namespace quantdata {

class CManager
{
public:
	using TStringView       = std::string_view;
	using TStringArray      = std::vector<TStringView>;
	using TSymbolArray      = std::vector<TQuantDataSymbolInfo>;
	using TSymbolMultiArray = std::vector<TSymbolArray>;
	using TPeriodArray      = std::vector<TQuantDataPeriod>;

	struct SProviderInfo
	{
		TStringArray      symbolSources;
		TSymbolMultiArray nativeSymbolsArray;
		TPeriodArray      periods;
	};

private:
	using TProviderInfos = std::array<SProviderInfo, CQuantDataProvider::count()>;

public:
	CManager();

	EQuantDataResult Init();
	EQuantDataResult Shutdown();
	EQuantDataResult CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings);

	inline bool IsInitialized() const
	{
		return m_isInitialized;
	}

	inline const SProviderInfo& GetProviderInfo(EQuantDataProvider provider) const
	{
		return m_providerInfos[CQuantDataProvider(provider).ordinal()];
	}

private:
	template <class Type, size_t Size>
	void BuildSymbolSourcesFor(const CQuantDataProvider& provider, const Type(&sources)[Size]);
	void BuildSymbolSources();
	template <class Type, size_t Size>
	void BuildNativeSymbolsFor(const CQuantDataProvider& provider, const Type(&symbols)[Size]);
	void BuildNativeSymbols();
	void BuildPeriods();
	
	TProviderInfos m_providerInfos;
	bool m_isInitialized = false;
};

} // namespace quantdata
