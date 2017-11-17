
#pragma once

#include <quantdata.h>

namespace quantdata {

inline bool IsValidProvider(const TQuantDataProviderSettings* pSettings)
{
	return pSettings
		&& CQuantDataProvider(pSettings->provider).is_valid()
		&& is_valid_string(pSettings->apikey);
}

inline bool IsValidDownload(const TQuantDataDownloadSettings* pSettings)
{
	return pSettings
		&& is_valid_string(pSettings->symbol);
}

} // namespace quantdata
