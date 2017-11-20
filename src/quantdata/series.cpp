
#include "series.h"
#include <common/util.h>
#include <common/stl.h>
#include <quantdata/manager.h>
#include <quantdata/checks.h>

// https://quant.stackexchange.com/questions/141/what-data-sources-are-available-online

namespace quantdata {

CSeries::CSeries(const CManager& manager, const TAllocatorFunctions& allocFunctions)
	: m_manager(manager)
	, m_allocFunctions(allocFunctions)
	, m_stringAllocator(allocFunctions)
	, m_provider(m_stringAllocator)
{}

EQuantDataResult CSeries::SetProvider(const TQuantDataProviderSettings* pSettings)
{
	if (!IsValidProvider(pSettings))
		return EQuantDataResult::InvalidProvider;

	m_provider.Set(*pSettings);
	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetNativePeriods(IQuantDataPeriods** ppPeriods)
{
	if (!ppPeriods)
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	auto& providerInfo = m_manager.GetProviderInfo(m_provider.type);
	auto periodArray = mem::placement_alloc<TPeriodArray>(m_allocFunctions.alloc(), providerInfo.periods, m_allocFunctions);
	*ppPeriods = periodArray;

	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetSupportedSymbols(TQuantDataSymbols** ppSymbols)
{
	// https://www.alphavantage.co/physical_currency_list/
	// https://www.alphavantage.co/digital_currency_list/

	if (!ppSymbols)
		return EQuantDataResult::InvalidArgument;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::Download(const TQuantDataDownloadSettings* pSettings)
{
	if (!IsValidDownload(pSettings))
		return EQuantDataResult::InvalidArgument;

	if (!m_manager.IsInitialized())
		return EQuantDataResult::NotInitialized;

	if (!m_provider.Valid())
		return EQuantDataResult::InvalidProvider;

	TDownloader::TData header(m_stringAllocator);
	TDownloader::TData page(m_stringAllocator);
	TDownloader::SDownloadSettings dlsettings;
	TDownloader::SDownloadInfo dlinfo;

	TString url = stl::string_format_t<TString>(m_stringAllocator,
		"https://www.alphavantage.co/"
		"query?function=TIME_SERIES_INTRADAY"
		"&symbol=%s&interval=1min&apikey=demo&datatype=csv", pSettings->symbol);

	dlsettings.url = url.c_str();
	dlsettings.certtype = m_provider.certtype.c_str();
	dlsettings.certfile = m_provider.certfile.c_str();
	CURLcode code = TDownloader::Download(dlsettings, &header, &page, &dlinfo);

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
	mem::placement_free(this, m_allocFunctions.free());
	return EQuantDataResult::Success;
}

} // namespace quantdata
