
#pragma once

#include <quantdata.h>
#include <common/util.h>
#include <utility>

namespace quantdata {

class CManager;

template <class Implementation>
class CHubFunctions : public Implementation
{
private:
	using TThis               = CHubFunctions;
	using TImplementation     = Implementation;
	using TInterface          = typename TImplementation::TInterface;
	using TInterfaceFunctions = typename TInterface::TInterfaceFunctions;

public:
	template <class... Args>
	CHubFunctions(Args&&... args)
		: TImplementation(std::forward<Args>(args)...)
	{
		auto& mutableFunctions = const_cast<TInterfaceFunctions&>(m_functions);
		util::nullify_object_debug(mutableFunctions);

		mutableFunctions.SetProvider  = Static_SetProvider;
		mutableFunctions.GetPeriods   = Static_GetPeriods;
		mutableFunctions.GetSymbols   = Static_GetSymbols;
		mutableFunctions.DownloadOhlc = Static_DownloadOhlc;
		mutableFunctions.DownloadTick = Static_DownloadTick;
		mutableFunctions.LoadOhlc     = Static_LoadOhlc;
		mutableFunctions.LoadTick     = Static_LoadTick;
		mutableFunctions.Release      = Static_Release;

		util::verify_initialized_pointers_debug(m_functions);
		util::verify_equal_pointers_debug(&m_functions, static_cast<TInterface*>(this));
	}

private:
	UTILS_DELETE_COPY_CONSTRUCTOR(TThis)

private:
	static EQuantDataResult QUANTDATA_CALL Static_SetProvider(TInterface* pThis, const TQuantDataProviderSettings* pSettings) {
		return static_cast<TThis*>(pThis)->SetProvider(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetPeriods(TInterface* pThis, IQuantDataPeriods** ppPeriods) {
		return static_cast<TThis*>(pThis)->GetPeriods(ppPeriods);
	}
	static EQuantDataResult QUANTDATA_CALL Static_GetSymbols(TInterface* pThis, IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings) {
		return static_cast<TThis*>(pThis)->GetSymbols(ppSymbols, pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_DownloadOhlc(TInterface* pThis, IQuantDataOhlc** ppOhlc, const TQuantDataDownloadSettings* pSettings) {
		return static_cast<TThis*>(pThis)->DownloadOhlc(ppOhlc, pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_DownloadTick(TInterface* pThis, IQuantDataTick** ppTick, const TQuantDataDownloadSettings* pSettings) {
		return static_cast<TThis*>(pThis)->DownloadTick(ppTick, pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_LoadOhlc(TInterface* pThis, IQuantDataOhlc** ppOhlc, const TQuantDataLoadSettings* pSettings) {
		return static_cast<TThis*>(pThis)->LoadOhlc(ppOhlc, pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_LoadTick(TInterface* pThis, IQuantDataTick** ppTick, const TQuantDataLoadSettings* pSettings) {
		return static_cast<TThis*>(pThis)->LoadTick(ppTick, pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Release(TInterface* pThis) {
		return static_cast<TThis*>(pThis)->Release();
	}
};

} // namespace quantdata
