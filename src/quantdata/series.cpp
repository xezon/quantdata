
#include "series.h"

namespace quantdata {

EQuantDataResult CDefaultSeries::SetApiKey(TQuantDataString apikey)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::GetSupportedIntervals(TQuantDataIntervals* pIntervals)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::GetSupportedSymbols(TQuantDataSymbols* pSymbols)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::Download(TQuantDataDownloadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::Load(TQuantDataLoadSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::Save(TQuantDataSaveSettings* pSettings) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::GetT1(TQuantDataT1s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::GetT2(TQuantDataT2s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::GetT6(TQuantDataT6s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::GetT8(TQuantDataT8s* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::GetGtData(TQuantDataGtDataPoints* pData) const
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::SetT1(TQuantDataT1s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::SetT2(TQuantDataT2s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::SetT6(TQuantDataT6s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::SetT8(TQuantDataT8s* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::SetGtData(TQuantDataGtDataPoints* pData)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CDefaultSeries::Release()
{
	return EQuantDataResult::Success;
}

} // namespace quantdata
