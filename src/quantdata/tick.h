
#pragma once

#include <quantdata/tick_functions.h>

namespace quantdata {

class CTick : public IQuantDataTickBucket
{
protected:
	using TInterface = IQuantDataTickBucket;

protected:
	CTick() {};

	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings);
	EQuantDataResult Release();

private:

};

} // namespace quantdata