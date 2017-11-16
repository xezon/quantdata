
#include "series.h"
#include <common/utils.h>
#include <quantdata/manager.h>

namespace quantdata {

CSeries::CSeries(CManager& manager, const utils::custom_allocator_functions& functions)
	: m_manager(manager)
	, m_functions(functions)
	, m_stringAllocator(functions)
	, m_apikey(m_stringAllocator)
	, m_certtype(m_stringAllocator)
	, m_certfile(m_stringAllocator)
{}

EQuantDataResult CSeries::SetProvider(const TQuantDataProviderSettings* pSettings)
{
	if (!pSettings)
		return EQuantDataResult::InvalidArgument;

	if (!IsValidProvider(*pSettings))
		return EQuantDataResult::InvalidProvider;

	m_provider = pSettings->provider;
	m_apikey = pSettings->apikey;
	m_certtype = IsValidString(pSettings->certtype) ? pSettings->certtype : "";
	m_certfile = IsValidString(pSettings->certfile) ? pSettings->certfile : "";

	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetSupportedIntervals(TQuantDataIntervals** ppIntervals)
{
	if (!ppIntervals)
		return EQuantDataResult::InvalidArgument;

	if (!HasValidProvider())
		return EQuantDataResult::InvalidProvider;

	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::GetSupportedSymbols(TQuantDataSymbols** ppSymbols)
{
	if (!ppSymbols)
		return EQuantDataResult::InvalidArgument;

	if (!HasValidProvider())
		return EQuantDataResult::InvalidProvider;

	return EQuantDataResult::Success;
}

EQuantDataResult CSeries::Download(const TQuantDataDownloadSettings* pSettings)
{
	if (!pSettings)
		return EQuantDataResult::InvalidArgument;

	if (!m_manager.IsInitialized())
		return EQuantDataResult::NotInitialized;

	if (!HasValidProvider())
		return EQuantDataResult::InvalidProvider;

	TDownloader::TData header(m_stringAllocator);
	TDownloader::TData page(m_stringAllocator);
	TDownloader::SDownloadSettings dlsettings;
	TDownloader::SDownloadInfo dlinfo;
	dlsettings.url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=MSFT&interval=1min&apikey=demo&datatype=csv";
	dlsettings.certtype = m_certtype.c_str();
	dlsettings.certfile = m_certfile.c_str();
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
	utils::PlacementFree(this, m_functions.free);
	return EQuantDataResult::Success;
}

bool CSeries::IsValidProvider(const TQuantDataProviderSettings& settings)
{
	return settings.provider.is_valid() && IsValidString(settings.apikey);
}

bool CSeries::HasValidProvider() const
{
	return m_provider.is_valid() && !m_apikey.empty();
}

EQuantDataResult CSeries::DownloadFromAlphaVantage(const TQuantDataDownloadSettings& settings)
{
	return EQuantDataResult::Success;
}

} // namespace quantdata
