
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <common/util.h>
#include <common/mem.h>
#include <utility>

namespace quantdata {

struct SProvider
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
		symbolInfo.name = std::move(json.at(0).as<string>());
		symbolInfo.desc = std::move(json.at(1).as<string>());
		return symbolInfo;
	}

	static Json to_json(const quantdata::SSymbolInfo& symbolInfo)
	{
		return Json::make_array({symbolInfo.name, symbolInfo.desc});
	}
};

} // namespace jsoncons
