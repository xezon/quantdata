
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <common/util.h>
#include <common/mem.h>

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

} // namespace quantdata
