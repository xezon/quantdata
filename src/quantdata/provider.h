
#pragma once

#include <quantdata.h>
#include <quantdata/types.h>
#include <common/util.h>

namespace quantdata {

struct SProvider
{
	SProvider(const TString::allocator_type& allocator)
		: type()
		, apikey(allocator)
		, certtype(allocator)
		, certfile(allocator)
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
	TString apikey;
	TString certtype;
	TString certfile;
};

} // namespace quantdata
