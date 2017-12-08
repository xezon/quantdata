
#pragma once

#include <quantdata/ohlc_functions.h>
#include <quantdata/types.h>

namespace quantdata {

class COhlcBucket : public IQuantDataOhlcBucket
{
protected:
	using TInterface = IQuantDataOhlcBucket;

protected:
	COhlcBucket(
		TOhlcVector&& ohlcVector,
		CQuantDataProvider provider,
		TQuantDataPeriod period,
		EQuantDataTimezone timezone)
		: m_ohlcVector(std::move(ohlcVector))
		, m_provider(provider)
		, m_period(period)
		, m_timezone(timezone)
	{};

	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings);
	EQuantDataResult Release();

private:
	const TOhlcVector        m_ohlcVector;
	const CQuantDataProvider m_provider;
	const TQuantDataPeriod   m_period;
	const EQuantDataTimezone m_timezone;
};

} // namespace quantdata
