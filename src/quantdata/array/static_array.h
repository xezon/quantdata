
#pragma once

#include <quantdata/array/array_functions.h>
#include <common/mem.h>

namespace quantdata {

template <class Interface, class Element>
class CStaticArray : public Interface
{
protected:
	using TInterface = Interface;
	using TElement   = Element;

protected:
	template <class Container>
	CStaticArray(const Container& container)
		: m_pElements(container.data())
		, m_size(container.size())
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
		mem::placement_g_free(this);
	}

private:
	const TElement*      m_pElements;
	const TQuantDataSize m_size;
};

} // namespace quantdata
