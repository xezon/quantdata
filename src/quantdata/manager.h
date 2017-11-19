
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <vector>
#include <array>

namespace quantdata {

class CManager
{
public:
	using TPeriodVector = std::vector<TQuantDataPeriod>;
	struct SProviderInfo { TPeriodVector periods; };

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
	void BuildProviderInfos();
	TAllocatorFunctions GetAllocatorFunctions(const TQuantDataCreationSettings* pSettings);
	
	TProviderInfos m_providerInfos;
	bool m_isInitialized = false;
};

} // namespace quantdata
