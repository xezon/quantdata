
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
#define QUANTDATA_IMPORT_OR_EXPORT QUANTDATA_EXPORT
#else
#define QUANTDATA_IMPORT_OR_EXPORT QUANTDATA_IMPORT
#endif

#ifdef __cplusplus
#define ZERO_INIT = {}
#define FTHIS(type) struct type* pThis
#define ITYPE(type, name) typedef struct type name;
#else
#define ZERO_INIT
#define FTHIS(type) const struct type##Functions* pThis
#define ITYPE(type, name) typedef const struct type##Functions name;
#endif
#ifdef ZORRO_LITE_C
#define FPTR(name)  QUANTDATA_CALL  name
#else
#define FPTR(name) (QUANTDATA_CALL* name)
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

#define QuantDataFormat_csv    0
#define QuantDataFormat_json   1
#define QuantDataFormat_t1    10 // zorro tick data
#define QuantDataFormat_t2    11 // zorro order book data
#define QuantDataFormat_t6    12 // zorro standard time series
#define QuantDataFormat_t8    13 // zorro contracts
#define QuantDataFormat_gtick 20 // genotick data

#ifdef __cplusplus

#include <data_enum.h>

#ifdef QUANTDATA_IMPL
#define QUANTDATA_DEFINE_ENUM_CLASS(clazz, underlying_t, list, meta_t) DEFINE_DATA_ENUM_CLASS(clazz, underlying_t, list, meta_t)
#else
#define QUANTDATA_DEFINE_ENUM_CLASS(clazz, underlying_t, list, meta_t) DEFINE_NORMAL_ENUM_CLASS(clazz, underlying_t, list)
#endif

enum class EQuantDataResult : int32_t
{
	Success             = QuantDataResult_Success,
	Failure             = QuantDataResult_Failure,
	NotInitialized      = QuantDataResult_NotInitialized,
	InvalidArgument     = QuantDataResult_InvalidArgument,
	InvalidApiKey       = QuantDataResult_InvalidApiKey,
	RejectedApiKey      = QuantDataResult_RejectedApiKey,
	UnsupportedInterval = QuantDataResult_UnsupportedInterval,
	UnsupportedSymbol   = QuantDataResult_UnsupportedSymbol,
	UnsupportedTime     = QuantDataResult_UnsupportedTime,
};


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

#ifdef __cplusplus
struct SQuantDataSeries;
#endif

struct SQuantDataSeriesFunctions
{
	EQuantDataResult FPTR(SetProvider)(FTHIS(SQuantDataSeries), const TQuantDataProviderSettings* pSettings);
	EQuantDataResult FPTR(GetSupportedIntervals)(FTHIS(SQuantDataSeries), TQuantDataIntervals* pIntervals);
	EQuantDataResult FPTR(GetSupportedSymbols)(FTHIS(SQuantDataSeries), TQuantDataSymbols* pSymbols);
	EQuantDataResult FPTR(Download)(FTHIS(SQuantDataSeries), const TQuantDataDownloadSettings* pSettings);
	EQuantDataResult FPTR(Load)(FTHIS(SQuantDataSeries), const TQuantDataLoadSettings* pSettings);
	EQuantDataResult FPTR(Save)(FTHIS(SQuantDataSeries), const TQuantDataSaveSettings* pSettings);
	EQuantDataResult FPTR(GetT1)(FTHIS(SQuantDataSeries), TQuantDataT1s* pData);
	EQuantDataResult FPTR(GetT2)(FTHIS(SQuantDataSeries), TQuantDataT2s* pData);
	EQuantDataResult FPTR(GetT6)(FTHIS(SQuantDataSeries), TQuantDataT6s* pData);
	EQuantDataResult FPTR(GetT8)(FTHIS(SQuantDataSeries), TQuantDataT8s* pData);
	EQuantDataResult FPTR(GetGtick)(FTHIS(SQuantDataSeries), TQuantDataGtDataPoints* pData);
	EQuantDataResult FPTR(SetT1)(FTHIS(SQuantDataSeries), TQuantDataT1s* pData);
	EQuantDataResult FPTR(SetT2)(FTHIS(SQuantDataSeries), TQuantDataT2s* pData);
	EQuantDataResult FPTR(SetT6)(FTHIS(SQuantDataSeries), TQuantDataT6s* pData);
	EQuantDataResult FPTR(SetT8)(FTHIS(SQuantDataSeries), TQuantDataT8s* pData);
	EQuantDataResult FPTR(SetGtick)(FTHIS(SQuantDataSeries), TQuantDataGtDataPoints* pData);
	EQuantDataResult FPTR(Release)(FTHIS(SQuantDataSeries));
};
ITYPE(SQuantDataSeries, IQuantDataSeries)

struct SQuantDataSeries
{
	const struct SQuantDataSeriesFunctions functions ZERO_INIT;
#ifdef __cplusplus
	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings) {
		return functions.SetProvider(this, pSettings);
	}
	EQuantDataResult GetSupportedIntervals(TQuantDataIntervals* pIntervals) {
		return functions.GetSupportedIntervals(this, pIntervals);
	}
	EQuantDataResult GetSupportedSymbols(TQuantDataSymbols* pSymbols) {
		return functions.GetSupportedSymbols(this, pSymbols);
	}
	EQuantDataResult Download(const TQuantDataDownloadSettings* pSettings) {
		return functions.Download(this, pSettings);
	}
	EQuantDataResult Load(const TQuantDataLoadSettings* pSettings) {
		return functions.Load(this, pSettings);
	}
	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings) {
		return functions.Save(this, pSettings);
	}
	EQuantDataResult GetT1(TQuantDataT1s* pData) {
		return functions.GetT1(this, pData);
	}
	EQuantDataResult GetT2(TQuantDataT2s* pData) {
		return functions.GetT2(this, pData);
	}
	EQuantDataResult GetT6(TQuantDataT6s* pData) {
		return functions.GetT6(this, pData);
	}
	EQuantDataResult GetT8(TQuantDataT8s* pData) {
		return functions.GetT8(this, pData);
	}
	EQuantDataResult GetGtick(TQuantDataGtDataPoints* pData) {
		return functions.GetGtick(this, pData);
	}
	EQuantDataResult SetT1(TQuantDataT1s* pData) {
		return functions.SetT1(this, pData);
	}
	EQuantDataResult SetT2(TQuantDataT2s* pData) {
		return functions.SetT2(this, pData);
	}
	EQuantDataResult SetT6(TQuantDataT6s* pData) {
		return functions.SetT6(this, pData);
	}
	EQuantDataResult SetT8(TQuantDataT8s* pData) {
		return functions.SetT8(this, pData);
	}
	EQuantDataResult SetGtick(TQuantDataGtDataPoints* pData) {
		return functions.SetGtick(this, pData);
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
QUANTDATA_IMPORT_OR_EXPORT EQuantDataResult QUANTDATA_CALL QuantDataCreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#undef ZERO_INIT

#endif // I_QUANTDATA_H
