
#pragma once

#include <quantdata/array/array_functions.h>
#include <common/mem.h>

namespace quantdata {

template <class Interface, class AllocatorFunctions>
class CStaticArray : public Interface
{
protected:
	using TInterface          = Interface;
	using TAllocatorFunctions = AllocatorFunctions;
	using TType               = typename TInterface::TType;

private:
	using TFree               = typename AllocatorFunctions::free_type;

protected:
	template <class Container>
	CStaticArray(const Container& container, const TAllocatorFunctions& allocFunctions)
		: m_pArray(container.data())
		, m_size(container.size())
		, m_free(allocFunctions.free())
	{
	}

	const TType* Get(TQuantDataSize index) const
	{
		return &m_pArray[index];
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
	const TType*         m_pArray;
	const TQuantDataSize m_size;
	const TFree          m_free;
};

} // namespace quantdata
