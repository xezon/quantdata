
#pragma once

#include <quantdata/tick_functions.h>

namespace quantdata {

class CTickBucket : public IQuantDataTickBucket
{
protected:
	using TInterface = IQuantDataTickBucket;

protected:
	CTickBucket() {};

	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings);
	EQuantDataResult Release();

private:

};

} // namespace quantdata
