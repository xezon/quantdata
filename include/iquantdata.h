
#ifndef I_QUANTDATA_H
#define I_QUANTDATA_H

#include <inttypes.h>

#ifdef QUANTDATA_IGNORE_ZORRO
typedef struct T1 {} T1;
typedef struct T2 {} T2;
typedef struct T6 {} T6;
typedef struct CONTRACT {} T8;
#else
#include <zorro.h>
typedef struct CONTRACT T8;
#endif
#ifdef QUANTDATA_IGNORE_GENOTICK
typedef struct SGenotickDataPoint {} TGenotickDataPoint;
#else
#include <igenotick.h>
#endif

#define QUANTDATA_EXPORT __declspec(dllexport)
#define QUANTDATA_IMPORT __declspec(dllimport)
#define QUANTDATA_CALL __cdecl

#ifdef QUANTDATA_IMPL
#define QUANTDATA_IMPORT_OR_EXPORT QUANTDATA_EXPORT
#else
#define QUANTDATA_IMPORT_OR_EXPORT QUANTDATA_IMPORT
#endif

#ifdef __cplusplus
#define QUANTDATA_ZERO_INIT = {}
#else
#define QUANTDATA_ZERO_INIT
#endif

#pragma pack(push, 4)

typedef const char* TQuantDataString;
typedef double      TQuantDataOletime;
typedef int64_t     TQuantDataUnixtime;
typedef uint32_t    TQuantDataSize;
typedef uint8_t     TQuantDataBool;

#define QuantDataResult_Success               0
#define QuantDataResult_InitFailed            1
#define QuantDataResult_CleanupFailed         2
#define QuantDataResult_InvalidApiKey       500
#define QuantDataResult_RejectedApiKey      501
#define QuantDataResult_UnsupportedInterval 600
#define QuantDataResult_UnsupportedSymbol   601
#define QuantDataResult_UnsupportedTime     602

#define QuantDataProvider_Quandl        0
#define QuantDataProvider_Oanda         1
#define QuantDataProvider_AlphaVantage  2
#define QuantDataProvider_CurrencyLayer 3

#define QuantDataInterval_Minute1  1
#define QuantDataInterval_Minute5  5
#define QuantDataInterval_Minute15 15
#define QuantDataInterval_Minute30 30
#define QuantDataInterval_Minute60 60
#define QuantDataInterval_Day1     1440
#define QuantDataInterval_Week1    10080
#define QuantDataInterval_Month1   43800

#define QuantDataFormat_csv   0
#define QuantDataFormat_json  1
#define QuantDataFormat_t1   10 // zorro tick data
#define QuantDataFormat_t2   11 // zorro order book data
#define QuantDataFormat_t6   12 // zorro standard time series
#define QuantDataFormat_t8   13 // zorro contracts
#define QuantDataFormat_gno  20 // genotick data

#ifdef __cplusplus

enum class EQuantDataResult : int32_t
{
	Success             = QuantDataResult_Success,
	InitFailed          = QuantDataResult_InitFailed,
	CleanupFailed       = QuantDataResult_CleanupFailed,
	InvalidApiKey       = QuantDataResult_InvalidApiKey,
	RejectedApiKey      = QuantDataResult_RejectedApiKey,
	UnsupportedInterval = QuantDataResult_UnsupportedInterval,
	UnsupportedSymbol   = QuantDataResult_UnsupportedSymbol,
	UnsupportedTime     = QuantDataResult_UnsupportedTime,
};

enum class EQuantDataProvider : int32_t
{
	Quandl        = QuantDataProvider_Quandl,
	Oanda         = QuantDataProvider_Oanda,
	AlphaVantage  = QuantDataProvider_AlphaVantage,
	CurrencyLayer = QuantDataProvider_CurrencyLayer,
};

enum class EQuantDataInterval : int32_t
{
	Invalid       = 0,
	Minute1       = QuantDataInterval_Minute1,
	Minute5       = QuantDataInterval_Minute5,
	Minute15      = QuantDataInterval_Minute15,
	Minute30      = QuantDataInterval_Minute30,
	Minute60      = QuantDataInterval_Minute60,
	Day1          = QuantDataInterval_Day1,
	Week1         = QuantDataInterval_Week1,
	Month1        = QuantDataInterval_Month1,
};

enum class EQuantDataFormat : int32_t
{
	csv  = QuantDataFormat_csv,
	json = QuantDataFormat_json,
	t1   = QuantDataFormat_t1,
	t2   = QuantDataFormat_t2,
	t6   = QuantDataFormat_t6,
	t8   = QuantDataFormat_t8,
	gno  = QuantDataFormat_gno,
};

#else

typedef int32_t EQuantDataResult;
typedef int32_t EQuantDataProvider;
typedef int32_t EQuantDataInterval;
typedef int32_t EQuantDataFormat;

#endif // __cplusplus

struct SQuantDataDownloadSettings
{
	TQuantDataUnixtime start        QUANTDATA_ZERO_INIT; // optional, default is begin of time
	TQuantDataUnixtime end          QUANTDATA_ZERO_INIT; // optional, default is end of time
	TQuantDataString   symbol       QUANTDATA_ZERO_INIT; // mandatory
	EQuantDataInterval interval     QUANTDATA_ZERO_INIT; // mandatory
	TQuantDataBool     adjusted     QUANTDATA_ZERO_INIT; // mandatory, might be unsupported
	TQuantDataBool     padding[3]   QUANTDATA_ZERO_INIT;
};
typedef SQuantDataDownloadSettings TQuantDataDownloadSettings;

struct SQuantDataSaveSettings
{
	TQuantDataString   utf8path     QUANTDATA_ZERO_INIT; // optional, default is working directory
	TQuantDataString   utf8filename QUANTDATA_ZERO_INIT; // optional, default is symbol name
	EQuantDataFormat   format       QUANTDATA_ZERO_INIT; // mandatory
};
typedef SQuantDataSaveSettings TQuantDataSaveSettings;

struct SQuantDataLoadSettings
{
	TQuantDataString   utf8filepath QUANTDATA_ZERO_INIT; // mandatory, path to file
};
typedef SQuantDataLoadSettings TQuantDataLoadSettings;

struct SQuantDataSeries;
struct SQuantDataSeriesFunctions;
#ifdef __cplusplus
typedef       struct SQuantDataSeries          IQuantDataSeries;
#else
typedef const struct SQuantDataSeriesFunctions IQuantDataSeries;
#endif

struct SQuantDataSeriesFunctions
{
	EQuantDataResult (QUANTDATA_CALL* SetApiKey)(IQuantDataSeries* pThis, TQuantDataString apikey);
	EQuantDataResult (QUANTDATA_CALL* GetSupportedIntervals)(IQuantDataSeries* pThis, EQuantDataInterval* pIntervals, TQuantDataSize* pCount);
	EQuantDataResult (QUANTDATA_CALL* GetSupportedSymbols)(IQuantDataSeries* pThis, TQuantDataString* pSymbols, TQuantDataSize* pCount);
	EQuantDataResult (QUANTDATA_CALL* Download)(IQuantDataSeries* pThis, TQuantDataDownloadSettings* pSettings);
	EQuantDataResult (QUANTDATA_CALL* Load)(IQuantDataSeries* pThis, TQuantDataString utf8Filepath);
	EQuantDataResult (QUANTDATA_CALL* Save)(IQuantDataSeries* pThis, TQuantDataSaveSettings* pSettings);
	EQuantDataResult (QUANTDATA_CALL* GetSize)(IQuantDataSeries* pThis, TQuantDataSize* pBarCount, TQuantDataSize* pOptionalColumnCount);
	EQuantDataResult (QUANTDATA_CALL* GetT1)(IQuantDataSeries* pThis, T1* pData);
	EQuantDataResult (QUANTDATA_CALL* GetT2)(IQuantDataSeries* pThis, T2* pData);
	EQuantDataResult (QUANTDATA_CALL* GetT6)(IQuantDataSeries* pThis, T6* pData);
	EQuantDataResult (QUANTDATA_CALL* GetT8)(IQuantDataSeries* pThis, T8* pData);
	EQuantDataResult (QUANTDATA_CALL* GetGno)(IQuantDataSeries* pThis, TGenotickDataPoint* pData);
	EQuantDataResult (QUANTDATA_CALL* SetT1)(IQuantDataSeries* pThis, T1* pData);
	EQuantDataResult (QUANTDATA_CALL* SetT2)(IQuantDataSeries* pThis, T2* pData);
	EQuantDataResult (QUANTDATA_CALL* SetT6)(IQuantDataSeries* pThis, T6* pData);
	EQuantDataResult (QUANTDATA_CALL* SetT8)(IQuantDataSeries* pThis, T8* pData);
	EQuantDataResult (QUANTDATA_CALL* SetGno)(IQuantDataSeries* pThis, TGenotickDataPoint* pData);
	EQuantDataResult (QUANTDATA_CALL* Release)(IQuantDataSeries* pThis);
};

struct SQuantDataSeries
{
	const struct SQuantDataSeriesFunctions functions QUANTDATA_ZERO_INIT;
#ifdef __cplusplus
	EQuantDataResult SetApiKey(TQuantDataString apikey) {
		return functions.SetApiKey(this, apikey);
	}
	EQuantDataResult GetSupportedIntervals(EQuantDataInterval* pIntervals, TQuantDataSize* pCount) {
		return functions.GetSupportedIntervals(this, pIntervals, pCount);
	}
	EQuantDataResult GetSupportedSymbols(TQuantDataString* pSymbols, TQuantDataSize* pCount) {
		return functions.GetSupportedSymbols(this, pSymbols, pCount);
	}
	EQuantDataResult Download(TQuantDataDownloadSettings* pSettings) {
		return functions.Download(this, pSettings);
	}
	EQuantDataResult Load(TQuantDataString utf8Filepath) {
		return functions.Load(this, utf8Filepath);
	}
	EQuantDataResult Save(TQuantDataSaveSettings* pSettings) {
		return functions.Save(this, pSettings);
	}
	EQuantDataResult GetSize(TQuantDataSize* pBarCount, TQuantDataSize* pOptionalColumnCount) {
		return functions.GetSize(this, pBarCount, pOptionalColumnCount);
	}
	EQuantDataResult GetT1(T1* pData) {
		return functions.GetT1(this, pData);
	}
	EQuantDataResult GetT2(T2* pData) {
		return functions.GetT2(this, pData);
	}
	EQuantDataResult GetT6(T6* pData) {
		return functions.GetT6(this, pData);
	}
	EQuantDataResult GetT8(T8* pData) {
		return functions.GetT8(this, pData);
	}
	EQuantDataResult GetGno(TGenotickDataPoint* pData) {
		return functions.GetGno(this, pData);
	}
	EQuantDataResult SetT1(T1* pData) {
		return functions.SetT1(this, pData);
	}
	EQuantDataResult SetT2(T2* pData) {
		return functions.SetT2(this, pData);
	}
	EQuantDataResult SetT6(T6* pData) {
		return functions.SetT6(this, pData);
	}
	EQuantDataResult SetT8(T8* pData) {
		return functions.SetT8(this, pData);
	}
	EQuantDataResult SetGno(TGenotickDataPoint* pData) {
		return functions.SetGno(this, pData);
	}
	EQuantDataResult Release() {
		return functions.Release(this);
	}
protected:
	SQuantDataSeries() {}
	~SQuantDataSeries() {}
#endif // __cplusplus
};

#ifdef __cplusplus
extern "C" {
#endif

QUANTDATA_IMPORT_OR_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataInit();
QUANTDATA_IMPORT_OR_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataCleanup();
QUANTDATA_IMPORT_OR_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataCreateSeries(IQuantDataSeries** ppSeries);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#undef QUANTDATA_ZERO_INIT

#endif // I_QUANTDATA_H
