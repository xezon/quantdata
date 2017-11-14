
#include "series.h"
#include <common/utils.h>

namespace quantdata {

EQuantDataResult CSeries::SetProvider(const TQuantDataProviderSettings* pSettings)
{
	if (!pSettings)
		return EQuantDataResult::InvalidArgument;

	if (!IsValidProvider(*pSettings))
		return EQuantDataResult::InvalidProvider;

	m_providerSettings = *pSettings;
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetSupportedIntervals(TQuantDataIntervals** ppIntervals)
{
	if (!ppIntervals)
		return EQuantDataResult::InvalidArgument;

	if (!IsValidProvider(m_providerSettings))
		return EQuantDataResult::InvalidProvider;

	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetSupportedSymbols(TQuantDataSymbols** ppSymbols)
{
	if (!ppSymbols)
		return EQuantDataResult::InvalidArgument;

	if (!IsValidProvider(m_providerSettings))
		return EQuantDataResult::InvalidProvider;

	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::Download(const TQuantDataDownloadSettings* pSettings)
{
	if (!pSettings)
		return EQuantDataResult::InvalidArgument;

	if (!IsValidProvider(m_providerSettings))
		return EQuantDataResult::InvalidProvider;

	switch (m_providerSettings.provider)
	{
	case EQuantDataProvider::AlphaVantage: return DownloadFromAlphaVantage(*pSettings);
	}

	return EQuantDataResult::Failure;
}

EQuantDataResult CSeries::Load(const TQuantDataLoadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::Save(const TQuantDataSaveSettings* pSettings) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetT1(TQuantDataT1s** ppData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetT2(TQuantDataT2s** ppData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetT6(TQuantDataT6s** ppData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetT8(TQuantDataT8s** ppData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetGtick(TQuantDataGtDataPoints** ppData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::SetT1(TQuantDataT1s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::SetT2(TQuantDataT2s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::SetT6(TQuantDataT6s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::SetT8(TQuantDataT8s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::SetGtick(TQuantDataGtDataPoints* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::Release()
{
	utils::PlacementFree(this, m_free);
	return EQuantDataResult::Success;
}

bool CSeries::IsValidProvider(const TQuantDataProviderSettings& settings)
{
	if (::IsValidString(settings.apikey) && settings.provider.is_valid())
	{
		return true;
	}
	return false;
}

EQuantDataResult CSeries::DownloadFromAlphaVantage(const TQuantDataDownloadSettings& settings)
{
	return EQuantDataResult::Success;
}

} // namespace quantdata
