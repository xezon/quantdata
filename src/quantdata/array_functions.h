
#pragma once

#include <common/util.h>
#include <utility>

namespace quantdata {

template <class Implementation>
class CArrayFunctions : public Implementation
{
private:
	using TThis               = CArrayFunctions;
	using TImplementation     = Implementation;
	using TElement            = typename TImplementation::TElement;
	using TInterface          = typename TImplementation::TInterface;
	using TInterfaceFunctions = typename TInterface::TInterfaceFunctions;

public:
	template <class... Args>
	CArrayFunctions(Args&&... args)
		: TImplementation(std::forward<Args>(args)...)
	{
		auto& mutableFunctions = const_cast<TInterfaceFunctions&>(m_functions);
		util::nullify_object_debug(mutableFunctions);

		mutableFunctions.Get = [](const TInterface* pThis, TQuantDataSize index) {
			return static_cast<const TThis*>(pThis)->Get(index);
		};
		mutableFunctions.Size = [](const TInterface* pThis) {
			return static_cast<const TThis*>(pThis)->Size();
		};
		mutableFunctions.Release = [](TInterface* pThis) {
			return static_cast<TThis*>(pThis)->Release();
		};

		util::verify_initialized_pointers_debug(m_functions);
		util::verify_equal_pointers_debug(&m_functions, static_cast<TInterface*>(this));
	}

private:
	UTILS_DELETE_COPY_CONSTRUCTOR(TThis)
};

} // namespace quantdata
