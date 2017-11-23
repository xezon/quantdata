
#pragma once

#include <quantdata/array/array_functions.h>
#include <quantdata/types.h>
#include <common/mem.h>
#include <utility>

namespace quantdata {

template <class Interface, class AllocatorFunctions, class Element, class Buffer = Element>
class CNewArray : public Interface
{
protected:
	using TInterface          = Interface;
	using TAllocatorFunctions = AllocatorFunctions;
	using TElement            = Element;
	using TBuffer             = Buffer;

public:
	using TElements           = TVector<TElement, TAllocatorFunctions>;
	using TElementsAllocator  = typename TElements::allocator_type;
	using TBuffers            = TVector<TBuffer, TAllocatorFunctions>;
	using TBuffersAllocator   = typename TBuffers::allocator_type;

	static TElements CreateElements(const TAllocatorFunctions& allocFunctions)
	{
		return TElements(TElementsAllocator(allocFunctions));
	}

	static TBuffers CreateBuffers(const TAllocatorFunctions& allocFunctions)
	{
		return TBuffers(TBuffersAllocator(allocFunctions));
	}
	
private:
	using TFree = typename TAllocatorFunctions::free_type;

protected:
	CNewArray(const TAllocatorFunctions& allocFunctions, TElements&& elements, TBuffers&& buffers)
		: m_elements(std::move(elements))
		, m_buffers(std::move(buffers))
		, m_free(allocFunctions.free())
	{}

	const TElement* Get(TQuantDataSize index) const
	{
		return &m_elements[index];
	}

	TQuantDataSize Size() const
	{
		return m_elements.size();
	}

	void Release()
	{
		mem::placement_free(this, m_free.free());
	}

private:
	const TElements m_elements;
	const TBuffers  m_buffers;
	const TFree     m_free;
};

} // namespace quantdata
