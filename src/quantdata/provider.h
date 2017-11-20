
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
	using TStringA            = TString<char, TAllocatorFunctions>;
	using TStringAllocatorA   = typename TStringA::allocator_type;

	SProvider(const TAllocatorFunctions& allocFunctions)
		: type()
		, apikey(TStringAllocatorA(allocFunctions))
		, certtype(TStringAllocatorA(allocFunctions))
		, certfile(TStringAllocatorA(allocFunctions))
	{}

	bool Valid() const
	{
		return type.is_valid() && !apikey.empty();
	}

	void Set(const TQuantDataProviderSettings& settings)
	{
		type = settings.provider;
		apikey = util::get_valid_string(settings.apikey);
		certtype = util::get_valid_string(settings.certtype);
		certfile = util::get_valid_string(settings.certfile);
	}

	CQuantDataProvider type;
	TStringA apikey;
	TStringA certtype;
	TStringA certfile;
};

} // namespace quantdata
