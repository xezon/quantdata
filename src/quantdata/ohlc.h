
#pragma once

#include <quantdata/ohlc_functions.h>

namespace quantdata {

class COhlc : public IQuantDataOhlc
{
protected:
	using TInterface = IQuantDataOhlc;

protected:
	COhlc() {};

	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings);
	EQuantDataResult Release();

private:

};

} // namespace quantdata
