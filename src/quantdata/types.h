
#pragma once

#include <common/mem.h>
#include <string>
#include <vector>

namespace quantdata {

template <class Type, class AllocatorFunctions>
using TAllocator = mem::custom_allocator<Type, AllocatorFunctions>;

template <class Type, class AllocatorFunctions>
using TString = std::basic_string<Type, std::char_traits<Type>, TAllocator<Type, AllocatorFunctions>>;

template <class AllocatorFunctions>
using TStringA = TString<char, AllocatorFunctions>;

template <class AllocatorFunctions>
using TStringAllocatorA = TAllocator<char, AllocatorFunctions>;

template <class Type, class AllocatorFunctions>
using TVector = std::vector<Type, TAllocator<Type, AllocatorFunctions>>;

} // namespace quantdata
