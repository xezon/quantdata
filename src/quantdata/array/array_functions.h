
#pragma once

#include <quantdata.h>
#include <common/util.h>

namespace quantdata {

class CManager;

template <class Implementation>
class CArrayFunctions : public Implementation
{
private:
	using TThis               = CArrayFunctions;
	using TImplementation     = Implementation;
	using TType               = typename TImplementation::TType;
	using TInterface          = typename TImplementation::TInterface;
	using TAllocatorFunctions = typename TImplementation::TAllocatorFunctions;
	using TInterfaceFunctions = typename TInterface::TInterfaceFunctions;

public:
	template <class Container>
	CArrayFunctions(const Container& container, const TAllocatorFunctions& allocFunctions)
		: TImplementation(container, allocFunctions)
	{
		auto& mutableFunctions = const_cast<TInterfaceFunctions&>(m_functions);
		util::nullify_object_debug(mutableFunctions);

		mutableFunctions.Get = Static_Get;
		mutableFunctions.Size = Static_Size;
		mutableFunctions.Release = Static_Release;

		util::verify_initialized_pointers_debug(m_functions);
		util::verify_equal_pointers_debug(&m_functions, static_cast<TInterface*>(this));
	}

private:
	UTILS_DELETE_COPY_CONSTRUCTOR(TThis)

private:
	static const TType* QUANTDATA_CALL Static_Get(TInterface* pThis, TQuantDataSize index) {
		return static_cast<TThis*>(pThis)->Get(index);
	}
	static TQuantDataSize QUANTDATA_CALL Static_Size(TInterface* pThis) {
		return static_cast<TThis*>(pThis)->Size();
	}
	static void QUANTDATA_CALL Static_Release(TInterface* pThis) {
		return static_cast<TThis*>(pThis)->Release();
	}
};

} // namespace quantdata
