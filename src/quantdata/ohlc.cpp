
#include <quantdata/ohlc.h>

#pragma warning(push)
#pragma warning(disable : 4100 4189)

namespace quantdata {

EQuantDataResult COhlcBucket::Save(const TQuantDataSaveSettings* pSettings)
{
	return EQuantDataResult::Success;
}

EQuantDataResult COhlcBucket::Release()
{
	return EQuantDataResult::Success;
}

} // namespace quantdata

#pragma warning(pop)
