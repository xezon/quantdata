
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

		mutableFunctions.SetProvider = [](TInterface* pThis, const TQuantDataProviderSettings* pSettings) {
			return static_cast<TThis*>(pThis)->SetProvider(pSettings);
		};
		mutableFunctions.GetPeriods = [](TInterface* pThis, IQuantDataPeriods** ppPeriods) {
			return static_cast<TThis*>(pThis)->GetPeriods(ppPeriods);
		},
		mutableFunctions.GetSymbols = [](TInterface* pThis, IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings) {
			return static_cast<TThis*>(pThis)->GetSymbols(ppSymbols, pSettings);
		},
		mutableFunctions.DownloadOhlc = [](TInterface* pThis, IQuantDataOhlcBucket** ppOhlc, const TQuantDataDownloadSettings* pSettings) {
			return static_cast<TThis*>(pThis)->DownloadOhlc(ppOhlc, pSettings);
		},
		mutableFunctions.DownloadTick = [](TInterface* pThis, IQuantDataTickBucket** ppTick, const TQuantDataDownloadSettings* pSettings) {
			return static_cast<TThis*>(pThis)->DownloadTick(ppTick, pSettings);
		},
		mutableFunctions.LoadOhlc = [](TInterface* pThis, IQuantDataOhlcBucket** ppOhlc, const TQuantDataLoadSettings* pSettings) {
			return static_cast<TThis*>(pThis)->LoadOhlc(ppOhlc, pSettings);
		},
		mutableFunctions.LoadTick = [](TInterface* pThis, IQuantDataTickBucket** ppTick, const TQuantDataLoadSettings* pSettings) {
			return static_cast<TThis*>(pThis)->LoadTick(ppTick, pSettings);
		},
		mutableFunctions.Release = [](TInterface* pThis) {
			static_cast<TThis*>(pThis)->Release();
		},

		util::verify_initialized_pointers_debug(m_functions);
		util::verify_equal_pointers_debug(&m_functions, static_cast<TInterface*>(this));
	}

private:
	UTILS_DELETE_COPY_CONSTRUCTOR(TThis)
};

} // namespace quantdata
