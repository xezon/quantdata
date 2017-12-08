
#pragma once

#include <quantdata/ohlc_functions.h>
#include <quantdata/types.h>
#include <common/mem.h>
#include <utility>

namespace quantdata {

class COhlcBucket : public IQuantDataOhlcBucket
{
protected:
	using TInterface = IQuantDataOhlcBucket;

protected:
	COhlcBucket(
		TOhlcVector&& ohlcVector,
		EQuantDataProvider provider,
		TQuantDataPeriod period,
		EQuantDataTimezone timezone)
		: m_ohlcVector(std::move(ohlcVector))
		, m_provider(provider)
		, m_period(period)
		, m_timezone(timezone)
	{};

	const TQuantDataOhlc* Get(TQuantDataSize index) const
	{
		return &m_ohlcVector.at(index);
	}

	TQuantDataSize Size() const
	{
		return m_ohlcVector.size();
	}

	EQuantDataProvider GetProvider() const
	{
		return m_provider;
	};

	TQuantDataPeriod GetPeriod() const
	{
		return m_period;
	};

	EQuantDataTimezone GetTimezone() const
	{
		return m_timezone;
	};

	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings) const;

	void Release()
	{
		mem::placement_g_free(this);
	}

private:
	TOhlcVector m_ohlcVector;
	const EQuantDataProvider m_provider;
	const TQuantDataPeriod   m_period;
	const EQuantDataTimezone m_timezone;
};

} // namespace quantdata
