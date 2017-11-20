
#pragma once

#include <quantdata/array/array_functions.h>
#include <common/mem.h>
#include <vector>

namespace quantdata {

template <class Interface, class AllocatorFunctions>
class CNewArray : public Interface
{
protected:
	using TInterface          = Interface;
	using TType               = typename Interface::TType;

private:
	using TAllocatorFunctions = AllocatorFunctions;
	using TFree               = typename AllocatorFunctions::free_type;
	using TAllocator          = mem::custom_allocator<TType, AllocatorFunctions>;
	using TVector             = std::vector<TType, TAllocator>;

protected:
	template <class Container>
	CNewArray(const Container& container, const TAllocatorFunctions& allocFunctions)
		: m_vector(container.cbegin(), container.cend(), TAllocator(allocFunctions))
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
