
#pragma once

#include <quantdata/array/array_functions.h>
#include <common/utils_mem.h>

namespace quantdata {

template <class Interface, class AllocatorFunctions>
class CStaticArray : public Interface
{
protected:
	using TInterface          = Interface;
	using TType               = typename Interface::TType;

private:
	using TAllocatorFunctions = AllocatorFunctions;
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
		utils::placement_free(this, m_free.free());
	}

private:
	const TType*         m_pArray;
	const TQuantDataSize m_size;
	const TFree          m_free;
};

} // namespace quantdata
