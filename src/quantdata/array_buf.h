
#pragma once

#include <quantdata/array_functions.h>
#include <common/mem.h>
#include <utility>

namespace quantdata {

struct empty_t {};

template <class Interface, class Elements, class Buffers = empty_t>
class CArrayBuf : public Interface
{
protected:
	using TInterface = Interface;

public:
	using TElements  = Elements;
	using TBuffers   = Buffers;
	using TElement   = typename TElements::value_type;

protected:
	CArrayBuf(TElements&& elements)
		: m_elements(std::move(elements))
	{}

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
