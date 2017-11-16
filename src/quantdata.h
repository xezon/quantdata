
#pragma once

#define DATA_ENUM_DEBUGGING 2
#define QUANTDATA_IMPL
#include <iquantdata.h>
#include <common/utils_c.h>

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
