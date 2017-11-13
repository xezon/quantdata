
#pragma once

#define QUANTDATA_IMPL
#include <iquantdata.h>

#define CURL_STATICLIB
#include <curl/curl.h>

#include <utils_c.h>

namespace quantdata {

inline TQuantDataAlloc GetDefaultAlloc()
{
	return Alloc;
}

inline TQuantDataFree GetDefaultFree()
{
	return Free;
}

} // namespace quantdata
