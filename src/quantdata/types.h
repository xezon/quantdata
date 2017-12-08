
#pragma once

#include <quantdata.h>
#include <common/util.h>
#include <common/mem.h>
#include <common/utf8.h>
#include <date/date.h>
#include <cpprest/http_client.h>
#pragma warning(push)
#pragma warning(disable : 4189 4100 4459)
#define JSONCONS_HAS_STRING_VIEW
#include <jsoncons/json.hpp>
#include <jsoncons_ext/csv/csv_reader.hpp>
#include <jsoncons_ext/csv/csv_serializer.hpp>
#pragma warning(pop)
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <utility>

namespace quantdata {

template <class Type>
using allocator = mem::globalf_allocator<Type>;

using string  = std::basic_string<char, std::char_traits<char>, allocator<char>>;
using wstring = std::basic_string<wchar_t, std::char_traits<wchar_t>, allocator<wchar_t>>;

using string_view  = std::string_view;
using wstring_view = std::wstring_view;

template <class Type>
using vector = std::vector<Type, allocator<Type>>;

using istringstream = std::basic_istringstream<char, std::char_traits<char>, allocator<char>>;
using ostringstream = std::basic_ostringstream<char, std::char_traits<char>, allocator<char>>;

using TOhlcVector = vector<SQuantDataOhlc>;
using TTickVector = vector<SQuantDataTick>;

using http_string    = utility::string_t;
using http_client    = web::http::client::http_client;
using http_request   = web::http::http_request;
using http_response  = web::http::http_response;
using status_code    = web::http::status_code;
using status_codes   = web::http::status_codes;
using http_exception = web::http::http_exception;
using http_methods   = web::http::methods;
using uri            = web::uri;
using uri_builder    = web::uri_builder;

inline string to_lower_ascii(const string_view& view)
{
	string str;
	str.reserve(view.size());
	for (char ch : view) {
		str.push_back(util::to_lower_ascii(ch));
	}
	return str;
}

namespace json {
using json = jsoncons::basic_json<char, jsoncons::preserve_order_policy, allocator<char>>;
using json_key_value_pair        = typename json::key_value_pair_type;
using json_string_view           = typename json::string_view_type;
using json_object_iterator       = typename json::object_iterator;
using const_json_object_iterator = typename json::const_object_iterator;
template <class Json>
using json_decoder   = jsoncons::json_decoder<Json>;
using json_exception = jsoncons::json_exception;
using csv_parameters = jsoncons::csv::basic_csv_parameters<char>;
using csv_reader     = jsoncons::csv::basic_csv_reader<char>;
using csv_serializer = jsoncons::csv::basic_csv_serializer<char>;

inline const_json_object_iterator find_similar(const json& value, const string_view& keyname)
{
	string keylower = to_lower_ascii(keyname);
	auto range = value.object_range();
	auto it = std::find_if(range.begin(), range.end(), 
		[&keylower](const json_key_value_pair& pair) {
		return to_lower_ascii(pair.key()).find(keylower) != json_string_view::npos;
	});
	return it;
}
} // namespace json

#ifdef _WIN32
inline utility::string_t to_web_string(const string_view& view)
{
	return utf8::to_ucs2(view.data(), view.data() + view.size());
}
inline utility::string_t to_web_string(const char* str)
{
	return utf8::to_ucs2(str);
}
#else
template <class String>
inline utility::string_t to_web_string(const string_view& view)
{
	return str;
}
inline utility::string_t to_web_string(const char* str)
{
	return str;
}
#endif

struct SProviderSettings
{
	void Reset()
	{
		type = CQuantDataProvider();
		apikey.clear();
		certtype.clear();
		certfile.clear();
	}

	void Set(const TQuantDataProviderSettings& settings)
	{
		type = settings.provider;
		apikey = util::get_valid_string(settings.apikey);
		certtype = util::get_valid_string(settings.certtype);
		certfile = util::get_valid_string(settings.certfile);
	}

	bool Valid() const
	{
		return type.is_valid() && !apikey.empty();
	}

	CQuantDataProvider type;
	string apikey;
	string certtype;
	string certfile;
};

struct SSymbolInfo
{
	void Set(const TQuantDataSymbolInfo& symbolInfo)
	{
		name = util::get_valid_string(symbolInfo.name);
		desc = util::get_valid_string(symbolInfo.desc);
	}

	TQuantDataSymbolInfo GetPod()
	{
		TQuantDataSymbolInfo obj;
		obj.name = this->name.c_str();
		obj.desc = this->desc.c_str();
		return obj;
	}

	string name;
	string desc;
};

using TSymbolInfos = vector<SSymbolInfo>;

} // namespace quantdata

namespace jsoncons {

template <class Json>
struct json_type_traits <Json, quantdata::SSymbolInfo>
{
	static const bool is_assignable = true;

	static bool is(const Json& json) noexcept
	{
		if (json.is_object())
			if (json.size() == 2)
				if (json.at(0).is_string())
					if (json.at(1).is_string())
						return true;
		return false;
	}

	static quantdata::SSymbolInfo as(const Json& json)
	{
		quantdata::SSymbolInfo symbolInfo;
		symbolInfo.name = std::move(json.at(0).as<quantdata::string>());
		symbolInfo.desc = std::move(json.at(1).as<quantdata::string>());
		return symbolInfo;
	}

	static Json to_json(const quantdata::SSymbolInfo& symbolInfo)
	{
		return Json::make_array({symbolInfo.name, symbolInfo.desc});
	}
};

} // namespace jsoncons
