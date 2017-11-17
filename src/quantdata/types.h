
#pragma once

#include <common/utils.h>
#include <string>

namespace quantdata {

using TAllocatorFunctions = utils::custom_allocator_functions;
using TStringAllocator = utils::custom_allocator<char>;
using TString = std::basic_string<char, std::char_traits<char>, TStringAllocator>;

} // namespace quantdata
