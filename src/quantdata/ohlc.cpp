
#include <quantdata/ohlc.h>

#pragma warning(push)
#pragma warning(disable : 4100 4189)

namespace quantdata {

EQuantDataResult COhlc::Save(const TQuantDataSaveSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult COhlc::Release()
{
	return EQuantDataResult::Success;
}

} // namespace quantdata

#pragma warning(pop)
