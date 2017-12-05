
#pragma once

#include <quantdata.h>
#include <common/util.h>
#include <utility>

namespace quantdata {

class CManager;

template <class Implementation>
class COhlcFunctions : public Implementation
{
private:
	using TThis               = COhlcFunctions;
	using TImplementation     = Implementation;
	using TInterface          = typename TImplementation::TInterface;
	using TInterfaceFunctions = typename TInterface::TInterfaceFunctions;

public:
	template <class... Args>
	COhlcFunctions(Args&&... args)
		: TImplementation(std::forward<Args>(args)...)
	{
		auto& mutableFunctions = const_cast<TInterfaceFunctions&>(m_functions);
		util::nullify_object_debug(mutableFunctions);

		mutableFunctions.Save    = Static_Save;
		mutableFunctions.Release = Static_Release;

		util::verify_initialized_pointers_debug(m_functions);
		util::verify_equal_pointers_debug(&m_functions, static_cast<TInterface*>(this));
	}

private:
	UTILS_DELETE_COPY_CONSTRUCTOR(TThis)

private:
	static EQuantDataResult QUANTDATA_CALL Static_Save(TInterface* pThis, const TQuantDataSaveSettings* pSettings) {
		return static_cast<TThis*>(pThis)->Save(pSettings);
	}
	static EQuantDataResult QUANTDATA_CALL Static_Release(TInterface* pThis) {
		return static_cast<TThis*>(pThis)->Release();
	}
};

} // namespace quantdata
