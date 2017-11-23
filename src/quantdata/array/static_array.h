
#pragma once

#include <quantdata/array/array_functions.h>
#include <common/mem.h>

namespace quantdata {

template <class Interface, class AllocatorFunctions, class Element>
class CStaticArray : public Interface
{
protected:
	using TInterface          = Interface;
	using TAllocatorFunctions = AllocatorFunctions;
	using TElement            = Element;

private:
	using TFree = typename TAllocatorFunctions::free_type;

protected:
	template <class Container>
	CStaticArray(const TAllocatorFunctions& allocFunctions, const Container& container)
		: m_pElements(container.data())
		, m_size(container.size())
		, m_free(allocFunctions.free())
	{
	}

	const TElement* Get(TQuantDataSize index) const
	{
		return &m_pElements[index];
	}

	TQuantDataSize Size() const
	{
		return m_size;
	}

	void Release()
	{
		mem::placement_free(this, m_free.free());
	}

private:
	const TElement*      m_pElements;
	const TQuantDataSize m_size;
	const TFree          m_free;
};

} // namespace quantdata
