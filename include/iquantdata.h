
#ifndef I_QUANTDATA_H
#define I_QUANTDATA_H

#include <commontypes.h>

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
#define QUANTDATA_IMPORT_EXPORT QUANTDATA_EXPORT
#else
#define QUANTDATA_IMPORT_EXPORT QUANTDATA_IMPORT
#endif

#ifdef __cplusplus
#define ZERO_INIT = {}
#else
#define ZERO_INIT
#endif

#pragma pack(push, 4)

typedef const char* TQuantDataString;
typedef double      TQuantDataOletime;
typedef int64_t     TQuantDataUnixtime;
typedef uint32_t    TQuantDataSize;
typedef uint8_t     TQuantDataBool;
#ifdef ZORRO_LITE_C
typedef void*       TQuantDataAlloc;
typedef void*       TQuantDataFree;
#else
typedef alloc_func  TQuantDataAlloc;
typedef free_func   TQuantDataFree;
#endif

#define QuantDataResult_Success               0
#define QuantDataResult_Failure               1
#define QuantDataResult_NotInitialized        2
#define QuantDataResult_InvalidArgument       3
#define QuantDataResult_InvalidProvider     500
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

#define QuantDataFormat_csv    0
#define QuantDataFormat_json   1
#define QuantDataFormat_t1    10 // zorro tick data
#define QuantDataFormat_t2    11 // zorro order book data
#define QuantDataFormat_t6    12 // zorro standard time series
#define QuantDataFormat_t8    13 // zorro contracts
#define QuantDataFormat_gtick 20 // genotick data

#ifdef __cplusplus

#include <common/enum.h>

#ifdef QUANTDATA_IMPL
#define QUANTDATA_DEFINE_ENUM_CLASS(clazz, underlying_t, list, meta_t) DEFINE_DATA_ENUM_CLASS(clazz, underlying_t, list, meta_t)
#else
#define QUANTDATA_DEFINE_ENUM_CLASS(clazz, underlying_t, list, meta_t) DEFINE_NORMAL_ENUM_CLASS(clazz, underlying_t, list)
#endif

#define QUANTDATA_ENUM_PROVIDER(e) \
	e(Quandl        , = QuantDataProvider_Quandl        , (false)) \
	e(Oanda         , = QuantDataProvider_Oanda         , (false)) \
	e(AlphaVantage  , = QuantDataProvider_AlphaVantage  , (false)) \
	e(CurrencyLayer , = QuantDataProvider_CurrencyLayer , (false)) \

QUANTDATA_DEFINE_ENUM_CLASS(EQuantDataProvider, int32_t, QUANTDATA_ENUM_PROVIDER, bool)

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
	csv   = QuantDataFormat_csv,
	json  = QuantDataFormat_json,
	t1    = QuantDataFormat_t1,
	t2    = QuantDataFormat_t2,
	t6    = QuantDataFormat_t6,
	t8    = QuantDataFormat_t8,
	gtick = QuantDataFormat_gtick,
};

enum class EQuantDataResult : int32_t
{
	Success             = QuantDataResult_Success,
	Failure             = QuantDataResult_Failure,
	NotInitialized      = QuantDataResult_NotInitialized,
	InvalidArgument     = QuantDataResult_InvalidArgument,
	InvalidProvider     = QuantDataResult_InvalidProvider,
	RejectedApiKey      = QuantDataResult_RejectedApiKey,
	UnsupportedInterval = QuantDataResult_UnsupportedInterval,
	UnsupportedSymbol   = QuantDataResult_UnsupportedSymbol,
	UnsupportedTime     = QuantDataResult_UnsupportedTime,
};

#else

typedef int32_t EQuantDataResult;
typedef int32_t EQuantDataProvider;
typedef int32_t EQuantDataInterval;
typedef int32_t EQuantDataFormat;

#endif // __cplusplus

struct SQuantDataCreationSettings
{
	TQuantDataAlloc    alloc        ZERO_INIT; // optional
	TQuantDataFree     free         ZERO_INIT; // optional
};
typedef struct SQuantDataCreationSettings TQuantDataCreationSettings;

struct SQuantDataProviderSettings
{
	EQuantDataProvider provider     ZERO_INIT; // mandatory
	TQuantDataString   apikey       ZERO_INIT; // mandatory
};
typedef struct SQuantDataProviderSettings TQuantDataProviderSettings;

struct SQuantDataDownloadSettings
{
	TQuantDataUnixtime start        ZERO_INIT; // optional, default is begin of time
	TQuantDataUnixtime end          ZERO_INIT; // optional, default is end of time
	TQuantDataString   symbol       ZERO_INIT; // mandatory
	EQuantDataInterval interval     ZERO_INIT; // mandatory
	TQuantDataBool     adjusted     ZERO_INIT; // mandatory, might be unsupported
	TQuantDataBool     padding[3]   ZERO_INIT;
};
typedef struct SQuantDataDownloadSettings TQuantDataDownloadSettings;

struct SQuantDataSaveSettings
{
	TQuantDataString   utf8path     ZERO_INIT; // optional, default is working directory
	TQuantDataString   utf8filename ZERO_INIT; // optional, default is symbol name
	EQuantDataFormat   format       ZERO_INIT; // mandatory
	TQuantDataBool     splitYears   ZERO_INIT; // optional
	TQuantDataBool     padding[3]   ZERO_INIT;
};
typedef struct SQuantDataSaveSettings TQuantDataSaveSettings;

struct SQuantDataLoadSettings
{
	TQuantDataString   utf8filepath ZERO_INIT; // mandatory, path to file
};
typedef struct SQuantDataLoadSettings TQuantDataLoadSettings;

struct SQuantDataSymbols
{
	TQuantDataString*   pBuffer    ZERO_INIT;
	TQuantDataSize      bufferSize ZERO_INIT;
	TQuantDataSize      actualSize ZERO_INIT;
};
typedef struct SQuantDataSymbols TQuantDataSymbols;

struct SQuantDataIntervals
{
	EQuantDataInterval* pBuffer    ZERO_INIT;
	TQuantDataSize      bufferSize ZERO_INIT;
	TQuantDataSize      actualSize ZERO_INIT;
};
typedef struct SQuantDataIntervals TQuantDataIntervals;

struct SQuantDataT1s
{
	T1*                 pBuffer    ZERO_INIT;
	TQuantDataSize      bufferSize ZERO_INIT;
	TQuantDataSize      actualSize ZERO_INIT;
};
typedef struct SQuantDataT1s TQuantDataT1s;

struct SQuantDataT2s
{
	T2*                 pBuffer    ZERO_INIT;
	TQuantDataSize      bufferSize ZERO_INIT;
	TQuantDataSize      actualSize ZERO_INIT;
};
typedef struct SQuantDataT2s TQuantDataT2s;

struct SQuantDataT6s
{
	T6*                 pBuffer    ZERO_INIT;
	TQuantDataSize      bufferSize ZERO_INIT;
	TQuantDataSize      actualSize ZERO_INIT;
};
typedef struct SQuantDataT6s TQuantDataT6s;

struct SQuantDataT8s
{
	T8*                 pBuffer    ZERO_INIT;
	TQuantDataSize      bufferSize ZERO_INIT;
	TQuantDataSize      actualSize ZERO_INIT;
};
typedef struct SQuantDataT8s TQuantDataT8s;

struct SQuantDataGtDataPoints
{
	TGenotickDataPoint* pBuffer                   ZERO_INIT;
	TQuantDataSize      bufferSize                ZERO_INIT;
	TQuantDataSize      actualSize                ZERO_INIT;
	TQuantDataSize      bufferOptionalColumnCount ZERO_INIT;
	TQuantDataSize      actualOptionalColumnCount ZERO_INIT;
};
typedef struct SQuantDataGtDataPoints TQuantDataGtDataPoints;

struct SQuantDataSeries;
typedef struct SQuantDataSeries IQuantDataSeries;

#ifdef __cplusplus
extern "C" {
#endif

QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantData_Init();
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantData_Cleanup();
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantData_CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings);

QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_SetProvider(IQuantDataSeries* pSeries, const TQuantDataProviderSettings* pSettings);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_GetSupportedIntervals(IQuantDataSeries* pSeries, TQuantDataIntervals** ppIntervals);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_GetSupportedSymbols(IQuantDataSeries* pSeries, TQuantDataSymbols** ppSymbols);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_Download(IQuantDataSeries* pSeries, const TQuantDataDownloadSettings* pSettings);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_Load(IQuantDataSeries* pSeries, const TQuantDataLoadSettings* pSettings);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_Save(IQuantDataSeries* pSeries, const TQuantDataSaveSettings* pSettings);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_GetT1(IQuantDataSeries* pSeries, TQuantDataT1s** ppData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_GetT2(IQuantDataSeries* pSeries, TQuantDataT2s** ppData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_GetT6(IQuantDataSeries* pSeries, TQuantDataT6s** ppData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_GetT8(IQuantDataSeries* pSeries, TQuantDataT8s** ppData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_GetGtick(IQuantDataSeries* pSeries, TQuantDataGtDataPoints** ppData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_SetT1(IQuantDataSeries* pSeries, TQuantDataT1s* pData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_SetT2(IQuantDataSeries* pSeries, TQuantDataT2s* pData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_SetT6(IQuantDataSeries* pSeries, TQuantDataT6s* pData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_SetT8(IQuantDataSeries* pSeries, TQuantDataT8s* pData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_SetGtick(IQuantDataSeries* pSeries, TQuantDataGtDataPoints* pData);
QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataSeries_Release(IQuantDataSeries* pSeries);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
struct SQuantDataSeries
{
	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings) {
		return QuantDataSeries_SetProvider(this, pSettings);
	}
	EQuantDataResult GetSupportedIntervals(TQuantDataIntervals** ppIntervals) {
		return QuantDataSeries_GetSupportedIntervals(this, ppIntervals);
	}
	EQuantDataResult GetSupportedSymbols(TQuantDataSymbols** ppSymbols) {
		return QuantDataSeries_GetSupportedSymbols(this, ppSymbols);
	}
	EQuantDataResult Download(const TQuantDataDownloadSettings* pSettings) {
		return QuantDataSeries_Download(this, pSettings);
	}
	EQuantDataResult Load(const TQuantDataLoadSettings* pSettings) {
		return QuantDataSeries_Load(this, pSettings);
	}
	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings) {
		return QuantDataSeries_Save(this, pSettings);
	}
	EQuantDataResult GetT1(TQuantDataT1s** ppData) {
		return QuantDataSeries_GetT1(this, ppData);
	}
	EQuantDataResult GetT2(TQuantDataT2s** ppData) {
		return QuantDataSeries_GetT2(this, ppData);
	}
	EQuantDataResult GetT6(TQuantDataT6s** ppData) {
		return QuantDataSeries_GetT6(this, ppData);
	}
	EQuantDataResult GetT8(TQuantDataT8s** ppData) {
		return QuantDataSeries_GetT8(this, ppData);
	}
	EQuantDataResult GetGtick(TQuantDataGtDataPoints** ppData) {
		return QuantDataSeries_GetGtick(this, ppData);
	}
	EQuantDataResult SetT1(TQuantDataT1s* pData) {
		return QuantDataSeries_SetT1(this, pData);
	}
	EQuantDataResult SetT2(TQuantDataT2s* pData) {
		return QuantDataSeries_SetT2(this, pData);
	}
	EQuantDataResult SetT6(TQuantDataT6s* pData) {
		return QuantDataSeries_SetT6(this, pData);
	}
	EQuantDataResult SetT8(TQuantDataT8s* pData) {
		return QuantDataSeries_SetT8(this, pData);
	}
	EQuantDataResult SetGtick(TQuantDataGtDataPoints* pData) {
		return QuantDataSeries_SetGtick(this, pData);
	}
	EQuantDataResult Release() {
		return QuantDataSeries_Release(this);
	}
protected:
	SQuantDataSeries() {}
	~SQuantDataSeries() {}
};
#endif

#pragma pack(pop)

#undef ZERO_INIT

#endif // I_QUANTDATA_H
