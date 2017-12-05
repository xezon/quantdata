
#pragma once

#include <quantdata/tick_functions.h>

namespace quantdata {

class CTick : public IQuantDataTick
{
protected:
	using TInterface = IQuantDataTick;

protected:
	CTick() {};

	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings);
	EQuantDataResult Release();

private:

};

} // namespace quantdata
