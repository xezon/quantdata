
#pragma once

#include <common/mem.h>
#include <string>
#include <vector>

namespace quantdata {

template <class Type>
using allocator = mem::globalf_allocator<Type>;

using string = std::basic_string<char, std::char_traits<char>, allocator<char>>;
using wstring = std::basic_string<wchar_t, std::char_traits<wchar_t>, allocator<wchar_t>>;

template <class Type>
using vector = std::vector<Type, allocator<Type>>;

} // namespace quantdata
