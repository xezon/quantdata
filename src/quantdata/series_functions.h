
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <common/util.h>

namespace quantdata {

class CManager;

template <class Implementation>
class CSeriesFunctions : public Implementation
{
private:
	using TThis               = CSeriesFunctions;
	using TImplementation     = Implementation;
	using TInterface          = typename TImplementation::TInterface;
	using TAllocatorFunctions = typename TImplementation::TAllocatorFunctions;
	using TInterfaceFunctions = typename TInterface::TInterfaceFunctions;

public:
	CSeriesFunctions(const CManager& manager, const TAllocatorFunctions& allocFunctions)
		: TImplementation(manager, allocFunctions)
	{
		auto& mutableFunctions = const_cast<TInterfaceFunctions&>(m_functions);
		util::nullify_object_debug(mutableFunctions);

		mutableFunctions.SetProvider         = Static_SetProvider;
		mutableFunctions.GetNativePeriods    = Static_GetNativePeriods;
		mutableFunctions.GetSupportedSymbols = Static_GetSupportedSymbols;
		mutableFunctions.Download            = Static_Download;
		mutableFunctions.Load                = Static_Load;
		mutableFunctions.Save                = Static_Save;
		mutableFunctions.GetT1               = Static_GetT1;
		mutableFunctions.GetT2               = Static_GetT2;
		mutableFunctions.GetT6               = Static_GetT6;
		mutableFunctions.GetT8               = Static_GetT8;
		mutableFunctions.GetGtick            = Static_GetGtick;
		mutableFunctions.SetT1               = Static_SetT1;
		mutableFunctions.SetT2               = Static_SetT2;
		mutableFunctions.SetT6               = Static_SetT6;
		mutableFunctions.SetT8               = Static_SetT8;
		mutableFunctions.SetGtick            = Static_SetGtick;
		mutableFunctions.Release             = Static_Release;

		util::verify_initialized_pointers_debug(m_functions);
		util::verify_equal_pointers_debug(&m_functions, static_cast<TInterface*>(this));
	}

private:
	UTILS_DELETE_COPY_CONSTRUCTOR(TThis)

private:
	static EQuantDataResult QUANTDATA_CALL Static_SetProvider(TInterface* pThis, const TQuantDataProviderSettings* pSettings) {
		return static_cast<TThis*>(pThis)->SetProvider(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetNativePeriods(TInterface* pThis, IQuantDataPeriods** ppPeriods) {
		return static_cast<TThis*>(pThis)->GetNativePeriods(ppPeriods);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetSupportedSymbols(TInterface* pThis, TQuantDataSymbols** ppSymbols) {
		return static_cast<TThis*>(pThis)->GetSupportedSymbols(ppSymbols);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Download(TInterface* pThis, const TQuantDataDownloadSettings* pSettings) {
		return static_cast<TThis*>(pThis)->Download(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Load(TInterface* pThis, const TQuantDataLoadSettings* pSettings) {
		return static_cast<TThis*>(pThis)->Load(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Save(TInterface* pThis, const TQuantDataSaveSettings* pSettings) {
		return static_cast<const TThis*>(pThis)->Save(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetT1(TInterface* pThis, TQuantDataT1s** ppData) {
		return static_cast<const TThis*>(pThis)->GetT1(ppData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetT2(TInterface* pThis, TQuantDataT2s** ppData) {
		return static_cast<const TThis*>(pThis)->GetT2(ppData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetT6(TInterface* pThis, TQuantDataT6s** ppData) {
		return static_cast<const TThis*>(pThis)->GetT6(ppData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetT8(TInterface* pThis, TQuantDataT8s** ppData) {
		return static_cast<const TThis*>(pThis)->GetT8(ppData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetGtick(TInterface* pThis, TQuantDataGtDataPoints** ppData) {
		return static_cast<const TThis*>(pThis)->GetGtick(ppData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetT1(TInterface* pThis, TQuantDataT1s* pData) {
		return static_cast<TThis*>(pThis)->SetT1(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetT2(TInterface* pThis, TQuantDataT2s* pData) {
		return static_cast<TThis*>(pThis)->SetT2(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetT6(TInterface* pThis, TQuantDataT6s* pData) {
		return static_cast<TThis*>(pThis)->SetT6(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetT8(TInterface* pThis, TQuantDataT8s* pData) {
		return static_cast<TThis*>(pThis)->SetT8(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_SetGtick(TInterface* pThis, TQuantDataGtDataPoints* pData) {
		return static_cast<TThis*>(pThis)->SetGtick(pData);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Release(TInterface* pThis) {
		return static_cast<TThis*>(pThis)->Release();
	}
};

} // namespace quantdata
