
#pragma once

#include <quantdata/array_functions.h>
#include <quantdata/types.h>
#include <common/mem.h>
#include <utility>

namespace quantdata {

template <class Interface, class Elements, class Buffers>
class CArrayBuf : public Interface
{
protected:
	using TInterface = Interface;

public:
	using TElements  = Elements;
	using TBuffers   = Buffers;
	using TElement   = typename TElements::value_type;
	using TBuffer    = typename TBuffers::value_type;

protected:
	CArrayBuf(TElements&& elements, TBuffers&& buffers)
		: m_elements(std::move(elements))
		, m_buffers(std::move(buffers))
	{}

	const TElement* Get(TQuantDataSize index) const
	{
		return &m_elements.at(index);
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
