
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <common/util.h>
#include <common/mem.h>

namespace quantdata {

template <class AllocatorFunctions>
struct SProvider
{
	using TAllocatorFunctions = AllocatorFunctions;

	SProvider(const TAllocatorFunctions& allocFunctions)
		: type()
		, apikey(TStringAllocatorA<TAllocatorFunctions>(allocFunctions))
		, certtype(TStringAllocatorA<TAllocatorFunctions>(allocFunctions))
		, certfile(TStringAllocatorA<TAllocatorFunctions>(allocFunctions))
	{}

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
	TStringA<TAllocatorFunctions> apikey;
	TStringA<TAllocatorFunctions> certtype;
	TStringA<TAllocatorFunctions> certfile;
};

template <class AllocatorFunctions>
struct SSymbolInfo
{
	using TAllocatorFunctions = AllocatorFunctions;

	SSymbolInfo(const TAllocatorFunctions& allocFunctions)
		: name(TStringAllocatorA<TAllocatorFunctions>(allocFunctions))
		, desc(TStringAllocatorA<TAllocatorFunctions>(allocFunctions))
	{}

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

	TStringA<TAllocatorFunctions> name;
	TStringA<TAllocatorFunctions> desc;
};

} // namespace quantdata
