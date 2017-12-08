
#include <quantdata/ohlc.h>

#pragma warning(push)
#pragma warning(disable : 4100 4189)

namespace quantdata {

EQuantDataResult COhlcBucket::Save(const TQuantDataSaveSettings* pSettings) const
{
	return EQuantDataResult::Success;
}

} // namespace quantdata

#pragma warning(pop)
