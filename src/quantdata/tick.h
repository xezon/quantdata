
#pragma once

#include <quantdata/tick_functions.h>
#include <common/mem.h>

namespace quantdata {

class CTickBucket : public IQuantDataTickBucket
{
protected:
	using TInterface = IQuantDataTickBucket;

protected:
	CTickBucket() {};

	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings) const;

	void Release()
	{
		mem::placement_g_free(this);
	}

private:

};

} // namespace quantdata
