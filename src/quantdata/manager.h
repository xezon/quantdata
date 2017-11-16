
#pragma once

#include <quantdata.h>
#include <common/utils.h>

namespace quantdata {

class CManager
{
public:
	EQuantDataResult Init();
	EQuantDataResult Shutdown();
	EQuantDataResult CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings);

	inline bool IsInitialized() { return m_isInitialized; }

private:
	utils::SAllocatorFunctions GetAllocatorFunctions(const TQuantDataCreationSettings* pSettings);

	bool m_isInitialized = false;
};

} // namespace quantdata
