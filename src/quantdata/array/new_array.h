
#pragma once

#include <quantdata/array/array_functions.h>
#include <quantdata/types.h>
#include <common/mem.h>

namespace quantdata {

template <class Interface, class AllocatorFunctions>
class CNewArray : public Interface
{
protected:
	using TInterface          = Interface;
	using TAllocatorFunctions = AllocatorFunctions;
	using TType               = typename TInterface::TType;

private:
	using TFree               = typename TAllocatorFunctions::free_type;
	using TVector             = TVector<TType, TAllocatorFunctions>;
	using TVectorAllocator    = typename TVector::allocator_type;

protected:
	template <class Container>
	CNewArray(const Container& container, const TAllocatorFunctions& allocFunctions)
		: m_vector(container.cbegin(), container.cend(), TVectorAllocator(allocFunctions))
		, m_free(allocFunctions.free())
	{
	}

	const TType* Get(TQuantDataSize index) const
	{
		return &m_vector[index];
	}

	TQuantDataSize Size() const
	{
		return m_vector.size();
	}

	void Release()
	{
		mem::placement_free(this, m_free.free());
	}

private:
	const TVector m_vector;
	const TFree   m_free;
};

} // namespace quantdata
