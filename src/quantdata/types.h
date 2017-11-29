
#pragma once

#include <common/mem.h>
#pragma warning(push )  
#pragma warning(disable : 4189 4100 4459)
#include <jsoncons/json.hpp>
#include <jsoncons/json_type_traits.hpp>
#include <jsoncons_ext/csv/csv_reader.hpp>
#include <jsoncons_ext/csv/csv_serializer.hpp>
#pragma warning(pop)
#include <string>
#include <vector>
#include <sstream>

namespace quantdata {

template <class Type>
using allocator = mem::globalf_allocator<Type>;

using string = std::basic_string<char, std::char_traits<char>, allocator<char>>;
using wstring = std::basic_string<wchar_t, std::char_traits<wchar_t>, allocator<wchar_t>>;

template <class Type>
using vector = std::vector<Type, allocator<Type>>;

using istringstream = std::basic_istringstream<char, std::char_traits<char>, allocator<char>>;
using ostringstream = std::basic_ostringstream<char, std::char_traits<char>, allocator<char>>;

namespace json {
using json = jsoncons::basic_json<char, jsoncons::preserve_order_policy, allocator<char>>;
template <class Json>
using json_decoder = jsoncons::json_decoder<Json>;
using json_exception = jsoncons::json_exception;
using csv_parameters = jsoncons::csv::csv_parameters;
using csv_reader = jsoncons::csv::csv_reader;
using csv_serializer = jsoncons::csv::csv_serializer;
} // namespace json

} // namespace quantdata
