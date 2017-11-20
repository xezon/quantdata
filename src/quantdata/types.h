
#pragma once

#include <common/util.h>
#include <string>

namespace quantdata {

using TAllocatorFunctions = mem::custom_allocator_functions;
template <class T>
using TCustomAllocator = mem::custom_allocator<T, TAllocatorFunctions>;
using TString = std::basic_string<char, std::char_traits<char>, TCustomAllocator<char>>;

} // namespace quantdata
