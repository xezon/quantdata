
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
		mutableFunctions.GetPeriods = [](const TInterface* pThis, IQuantDataPeriods** ppPeriods) {
			return static_cast<const TThis*>(pThis)->GetPeriods(ppPeriods);
		},
		mutableFunctions.GetSymbols = [](const TInterface* pThis, IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings) {
			return static_cast<const TThis*>(pThis)->GetSymbols(ppSymbols, pSettings);
		},
		mutableFunctions.DownloadOhlc = [](const TInterface* pThis, IQuantDataOhlcBucket** ppOhlc, const TQuantDataDownloadSettings* pSettings) {
			return static_cast<const TThis*>(pThis)->DownloadOhlc(ppOhlc, pSettings);
		},
		mutableFunctions.DownloadTick = [](const TInterface* pThis, IQuantDataTickBucket** ppTick, const TQuantDataDownloadSettings* pSettings) {
			return static_cast<const TThis*>(pThis)->DownloadTick(ppTick, pSettings);
		},
		mutableFunctions.LoadOhlc = [](const TInterface* pThis, IQuantDataOhlcBucket** ppOhlc, const TQuantDataLoadSettings* pSettings) {
			return static_cast<const TThis*>(pThis)->LoadOhlc(ppOhlc, pSettings);
		},
		mutableFunctions.LoadTick = [](const TInterface* pThis, IQuantDataTickBucket** ppTick, const TQuantDataLoadSettings* pSettings) {
			return static_cast<const TThis*>(pThis)->LoadTick(ppTick, pSettings);
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
