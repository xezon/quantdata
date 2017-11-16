
#pragma once

#include "quantdata.h"
#include <string>
#include <common/utils_mem.h>
#include <downloader.h>

namespace quantdata {

class CManager;

class CSeries : public IQuantDataSeries
{
private:
	using TStringAllocator = utils::CAllocatorWithFunc<char>;
	using TString = std::basic_string<char, std::char_traits<char>, TStringAllocator>;
	using TDownloader = CDownloader<TStringAllocator>;

public:
	CSeries(CManager& manager, const utils::SAllocatorFunctions& functions);

	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings);
	EQuantDataResult GetSupportedIntervals(TQuantDataIntervals** ppIntervals);
	EQuantDataResult GetSupportedSymbols(TQuantDataSymbols** ppSymbols);
	EQuantDataResult Download(const TQuantDataDownloadSettings* pSettings);
	EQuantDataResult Load(const TQuantDataLoadSettings* pSettings);
	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings) const;
	EQuantDataResult GetT1(TQuantDataT1s** ppData) const;
	EQuantDataResult GetT2(TQuantDataT2s** ppData) const;
	EQuantDataResult GetT6(TQuantDataT6s** ppData) const;
	EQuantDataResult GetT8(TQuantDataT8s** ppData) const;
	EQuantDataResult GetGtick(TQuantDataGtDataPoints** ppData) const;
	EQuantDataResult SetT1(TQuantDataT1s* pData);
	EQuantDataResult SetT2(TQuantDataT2s* pData);
	EQuantDataResult SetT6(TQuantDataT6s* pData);
	EQuantDataResult SetT8(TQuantDataT8s* pData);
	EQuantDataResult SetGtick(TQuantDataGtDataPoints* pData);
	EQuantDataResult Release();

private:
	static bool IsValidProvider(const TQuantDataProviderSettings& provider);
	bool HasValidProvider() const;
	EQuantDataResult DownloadFromAlphaVantage(const TQuantDataDownloadSettings& settings);

	CManager& m_manager;
	utils::SAllocatorFunctions m_functions;
	TStringAllocator m_stringAllocator;
	EQuantDataProvider m_provider;
	TString m_apikey;
	TString m_certtype;
	TString m_certfile;
};

} // namespace quantdata
