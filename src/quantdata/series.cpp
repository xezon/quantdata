
#include "series.h"
#include <utils.h>

namespace quantdata {

EQuantDataResult CQuantDataSeries::SetProvider(const TQuantDataProviderSettings* pSettings)
{
	if (!pSettings || !IsValidProvider(*pSettings))
		return EQuantDataResult::InvalidArgument;

	m_providerSettings = *pSettings;
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::GetSupportedIntervals(TQuantDataIntervals* pIntervals)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::GetSupportedSymbols(TQuantDataSymbols* pSymbols)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::Download(const TQuantDataDownloadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::Load(const TQuantDataLoadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::Save(const TQuantDataSaveSettings* pSettings) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::GetT1(TQuantDataT1s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::GetT2(TQuantDataT2s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::GetT6(TQuantDataT6s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::GetT8(TQuantDataT8s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::GetGtick(TQuantDataGtDataPoints* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::SetT1(TQuantDataT1s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::SetT2(TQuantDataT2s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::SetT6(TQuantDataT6s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::SetT8(TQuantDataT8s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::SetGtick(TQuantDataGtDataPoints* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CQuantDataSeries::Release()
{
	utils::PlacementFree(this, m_free);
	return EQuantDataResult::Success;
}

bool CQuantDataSeries::IsValidProvider(const TQuantDataProviderSettings& provider)
{
	if (!::IsValidString(provider.apikey))
	{
		return false;
	}
	
	return true;
}

} // namespace quantdata
