
#pragma once

#include <common/utils.h>
#include <string>

namespace quantdata {

using TAllocatorFunctions = utils::custom_allocator_functions;
template <class T>
using TCustomAllocator = utils::custom_allocator<T, TAllocatorFunctions>;
using TString = std::basic_string<char, std::char_traits<char>, TCustomAllocator<char>>;

} // namespace quantdata
