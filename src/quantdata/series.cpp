
#include "series.h"
#include <utils.h>

namespace quantdata {

EQuantDataResult CSeries::SetProvider(const TQuantDataProviderSettings* pSettings)
{
	if (!pSettings || !IsValidProvider(*pSettings))
		return EQuantDataResult::InvalidArgument;

	m_providerSettings = *pSettings;
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetSupportedIntervals(TQuantDataIntervals* pIntervals)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetSupportedSymbols(TQuantDataSymbols* pSymbols)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::Download(const TQuantDataDownloadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::Load(const TQuantDataLoadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::Save(const TQuantDataSaveSettings* pSettings) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetT1(TQuantDataT1s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetT2(TQuantDataT2s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetT6(TQuantDataT6s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetT8(TQuantDataT8s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetGtick(TQuantDataGtDataPoints* pData) const
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

bool CSeries::IsValidProvider(const TQuantDataProviderSettings& provider)
{
	if (!::IsValidString(provider.apikey))
	{
		return false;
	}
	
	return true;
}

} // namespace quantdata
