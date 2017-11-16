
#pragma once

#define DATA_ENUM_DEBUGGING 2
#define QUANTDATA_IMPL
#include <iquantdata.h>
#include <common/utils.h>

namespace quantdata {

inline TQuantDataAlloc GetDefaultAlloc()
{
	return utils::alloc;
}

inline TQuantDataFree GetDefaultFree()
{
	return utils::free;
}

} // namespace quantdata
