
#include <quantdata/tick.h>

#pragma warning(push)
#pragma warning(disable : 4100 4189)

namespace quantdata {

EQuantDataResult CTick::Save(const TQuantDataSaveSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult CTick::Release()
{
	return EQuantDataResult::Success;
}

} // namespace quantdata

#pragma warning(pop)
