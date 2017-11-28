
#pragma once

#include <quantdata/array/array_functions.h>
#include <quantdata/types.h>
#include <common/mem.h>
#include <utility>

namespace quantdata {

template <class Interface, class Element, class Buffer = Element>
class CNewArray : public Interface
{
protected:
	using TInterface = Interface;
	using TElement   = Element;
	using TBuffer    = Buffer;

public:
	using TElements  = vector<TElement>;
	using TBuffers   = vector<TBuffer>;

protected:
	CNewArray(TElements&& elements, TBuffers&& buffers)
		: m_elements(std::move(elements))
		, m_buffers(std::move(buffers))
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
		mem::placement_g_free(this);
	}

private:
	const TElements m_elements;
	const TBuffers  m_buffers;
};

} // namespace quantdata
