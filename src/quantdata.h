
#pragma once

#define DATA_ENUM_DEBUGGING 2
#define QUANTDATA_IMPL
#include <iquantdata.h>
#include <common/mem.h>

namespace quantdata {

inline TQuantDataAlloc GetDefaultAlloc()
{
	return mem::alloc;
}

inline TQuantDataFree GetDefaultFree()
{
	return mem::free;
}

} // namespace quantdata
