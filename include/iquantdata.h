
#ifndef I_QUANTDATA_H_
#define I_QUANTDATA_H_

#include <common/types.h>

#ifdef QUANTDATA_IGNORE_ZORRO
typedef struct T1 T1;
typedef struct T2 T2;
typedef struct T6 T6;
typedef struct CONTRACT T8;
#else
#include <zorro.h>
typedef struct CONTRACT T8;
#endif
#ifdef QUANTDATA_IGNORE_GENOTICK
typedef struct SGenotickDataPoint TGenotickDataPoint;
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
#define FTHIS(type)               struct type*
#define ITYPE(type, name) typedef struct type name;
#else
#define ZERO_INIT
#define FTHIS(type)               const struct type##Functions*
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
typedef alloc_func  TQuantDataAlloc;
typedef free_func   TQuantDataFree;

#define QuantDataResult_Success             0
#define QuantDataResult_Failure             1
#define QuantDataResult_InvalidArgument     2
#define QuantDataResult_InvalidProvider   500
#define QuantDataResult_NoDataAvailable   501
#define QuantDataResult_RejectedApiKey    502
#define QuantDataResult_HttpException     503
#define QuantDataResult_UnsupportedPeriod 600
#define QuantDataResult_UnsupportedSymbol 601
#define QuantDataResult_UnsupportedTime   602

#define QuantDataProvider_Quandl       0
#define QuantDataProvider_Oanda        1
#define QuantDataProvider_AlphaVantage 2
#define QuantDataProvider_OpenExchange 3
#define QuantDataProvider_TrueFx       4

#define QuantDataSymbolSource_Default               0
#define QuantDataSymbolSource_AV_DigitalCurrencies  0
#define QuantDataSymbolSource_AV_PhysicalCurrencies 1

#define QuantDataPeriod_Finest        0.0
#define QuantDataPeriod_Second5       1.0 / 12.0
#define QuantDataPeriod_Second10      1.0 / 6.0
#define QuantDataPeriod_Second15      1.0 / 4.0
#define QuantDataPeriod_Second30      1.0 / 2.0
#define QuantDataPeriod_Minute        1.0
#define QuantDataPeriod_Minute2       2.0
#define QuantDataPeriod_Minute4       4.0
#define QuantDataPeriod_Minute5       5.0
#define QuantDataPeriod_Minute10     10.0
#define QuantDataPeriod_Minute15     15.0
#define QuantDataPeriod_Minute30     30.0
#define QuantDataPeriod_Hour         60.0
#define QuantDataPeriod_Hour2       120.0 
#define QuantDataPeriod_Hour3       180.0
#define QuantDataPeriod_Hour4       240.0
#define QuantDataPeriod_Hour6       360.0
#define QuantDataPeriod_Hour8       480.0
#define QuantDataPeriod_Hour12      720.0
#define QuantDataPeriod_Day        1440.0
#define QuantDataPeriod_Week      10080.0
#define QuantDataPeriod_Month     43200.0
#define QuantDataPeriod_Quarter  129600.0
#define QuantDataPeriod_Annual   525600.0

#define QuantDataFormat_csv    0
#define QuantDataFormat_json   1
#define QuantDataFormat_t1    10 // zorro tick data
#define QuantDataFormat_t2    11 // zorro order book data
#define QuantDataFormat_t6    12 // zorro standard time series
#define QuantDataFormat_t8    13 // zorro contracts
#define QuantDataFormat_gtick 20 // genotick data

#ifdef __cplusplus

#include <common/enum.h>
#include <array>

#define QUANTDATA_PROVIDER_LIST(e) \
	e( Quandl       , = QuantDataProvider_Quandl       , 0 ) \
	e( Oanda        , = QuantDataProvider_Oanda        , 0 ) \
	e( AlphaVantage , = QuantDataProvider_AlphaVantage , 0 ) \
	e( OpenExchange , = QuantDataProvider_OpenExchange , 0 ) \
	e( TrueFx       , = QuantDataProvider_TrueFx       , 0 ) \

DEFINE_DATA_ENUM_CLASS(EQuantDataProvider, CQuantDataProvider, uint32_t, QUANTDATA_PROVIDER_LIST, int8_t)
#undef QUANTDATA_PROVIDER_LIST

#define QUANTDATA_PERIOD_LIST(e) \
	e( Finest   , QuantDataPeriod_Finest   , 0 ) \
	e( Second5  , QuantDataPeriod_Second5  , 0 ) \
	e( Second10 , QuantDataPeriod_Second10 , 0 ) \
	e( Second15 , QuantDataPeriod_Second15 , 0 ) \
	e( Second30 , QuantDataPeriod_Second30 , 0 ) \
	e( Minute   , QuantDataPeriod_Minute   , 0 ) \
	e( Minute2  , QuantDataPeriod_Minute2  , 0 ) \
	e( Minute4  , QuantDataPeriod_Minute4  , 0 ) \
	e( Minute5  , QuantDataPeriod_Minute5  , 0 ) \
	e( Minute10 , QuantDataPeriod_Minute10 , 0 ) \
	e( Minute15 , QuantDataPeriod_Minute15 , 0 ) \
	e( Minute30 , QuantDataPeriod_Minute30 , 0 ) \
	e( Hour     , QuantDataPeriod_Hour     , 0 ) \
	e( Hour2    , QuantDataPeriod_Hour2    , 0 ) \
	e( Hour3    , QuantDataPeriod_Hour3    , 0 ) \
	e( Hour4    , QuantDataPeriod_Hour4    , 0 ) \
	e( Hour6    , QuantDataPeriod_Hour6    , 0 ) \
	e( Hour8    , QuantDataPeriod_Hour8    , 0 ) \
	e( Hour12   , QuantDataPeriod_Hour12   , 0 ) \
	e( Day      , QuantDataPeriod_Day      , 0 ) \
	e( Week     , QuantDataPeriod_Week     , 0 ) \
	e( Month    , QuantDataPeriod_Month    , 0 ) \
	e( Quarter  , QuantDataPeriod_Quarter  , 0 ) \
	e( Annual   , QuantDataPeriod_Annual   , 0 ) \

DEFINE_DATA_FLOAT(TQuantDataPeriod, CQuantDataPeriod, double, QUANTDATA_PERIOD_LIST, int8_t)
#undef QUANTDATA_PERIOD_LIST

enum class EQuantDataSymbolSource : uint32_t
{
	Default               = QuantDataSymbolSource_Default,
	AV_DigitalCurrencies  = QuantDataSymbolSource_AV_DigitalCurrencies,
	AV_PhysicalCurrencies = QuantDataSymbolSource_AV_PhysicalCurrencies,
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
	Success           = QuantDataResult_Success,
	Failure           = QuantDataResult_Failure,
	InvalidArgument   = QuantDataResult_InvalidArgument,
	InvalidProvider   = QuantDataResult_InvalidProvider,
	NoDataAvailable   = QuantDataResult_NoDataAvailable,
	RejectedApiKey    = QuantDataResult_RejectedApiKey,
	HttpException     = QuantDataResult_HttpException,
	UnsupportedPeriod = QuantDataResult_UnsupportedPeriod,
	UnsupportedSymbol = QuantDataResult_UnsupportedSymbol,
	UnsupportedTime   = QuantDataResult_UnsupportedTime,
};

#else

typedef uint32_t EQuantDataProvider;
typedef double   TQuantDataPeriod;
typedef uint32_t EQuantDataSymbolSource;
typedef int32_t  EQuantDataFormat;
typedef int32_t  EQuantDataResult;

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
	TQuantDataString   certtype     ZERO_INIT; // optional, default is PEM
	TQuantDataString   certfile     ZERO_INIT; // optional
};
typedef struct SQuantDataProviderSettings TQuantDataProviderSettings;

struct SQuantDataSymbolInfo
{
	TQuantDataString   name         ZERO_INIT;
	TQuantDataString   desc         ZERO_INIT;
};
typedef struct SQuantDataSymbolInfo TQuantDataSymbolInfo;

struct SQuantDataSymbolsSettings
{
	EQuantDataSymbolSource index    ZERO_INIT; // optional, number to symbol list: provider may provide more than one list
	TQuantDataBool         download ZERO_INIT; // optional, if set 1: downloads symbol list from provider if available
};
typedef struct SQuantDataSymbolsSettings TQuantDataSymbolsSettings;

struct SQuantDataDownloadSettings
{
	TQuantDataUnixtime start        ZERO_INIT; // optional, default is begin of time
	TQuantDataUnixtime end          ZERO_INIT; // optional, default is end of time
	TQuantDataString   symbol       ZERO_INIT; // mandatory
	TQuantDataPeriod   period       ZERO_INIT; // mandatory
	TQuantDataBool     adjusted     ZERO_INIT; // mandatory, might be unsupported
};
typedef struct SQuantDataDownloadSettings TQuantDataDownloadSettings;

struct SQuantDataSaveSettings
{
	TQuantDataString   utf8path     ZERO_INIT; // optional, default is working directory
	TQuantDataString   utf8filename ZERO_INIT; // optional, default is symbol name
	EQuantDataFormat   format       ZERO_INIT; // mandatory
	TQuantDataBool     splitYears   ZERO_INIT; // optional
};
typedef struct SQuantDataSaveSettings TQuantDataSaveSettings;

struct SQuantDataLoadSettings
{
	TQuantDataString   utf8filepath ZERO_INIT; // mandatory, path to file
};
typedef struct SQuantDataLoadSettings TQuantDataLoadSettings;

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

// INTERFACES

struct SQuantDataPeriodsFunctions
{
	const TQuantDataPeriod* FPTR(Get)     (FTHIS(SQuantDataPeriods), TQuantDataSize index);
	TQuantDataSize          FPTR(Size)    (FTHIS(SQuantDataPeriods));
	void                    FPTR(Release) (FTHIS(SQuantDataPeriods));
};
ITYPE(SQuantDataPeriods, IQuantDataPeriods)

struct SQuantDataSymbolsFunctions
{
	const TQuantDataSymbolInfo* FPTR(Get)     (FTHIS(SQuantDataSymbols), TQuantDataSize index);
	TQuantDataSize              FPTR(Size)    (FTHIS(SQuantDataSymbols));
	void                        FPTR(Release) (FTHIS(SQuantDataSymbols));
};
ITYPE(SQuantDataSymbols, IQuantDataSymbols)

struct SQuantDataSeriesFunctions
{
	EQuantDataResult FPTR(SetProvider)        (FTHIS(SQuantDataSeries), const TQuantDataProviderSettings* pSettings);
	EQuantDataResult FPTR(GetNativePeriods)   (FTHIS(SQuantDataSeries), IQuantDataPeriods** ppPeriods);
	EQuantDataResult FPTR(GetSupportedSymbols)(FTHIS(SQuantDataSeries), IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings);
	EQuantDataResult FPTR(Download)           (FTHIS(SQuantDataSeries), const TQuantDataDownloadSettings* pSettings);
	EQuantDataResult FPTR(Load)               (FTHIS(SQuantDataSeries), const TQuantDataLoadSettings* pSettings);
	EQuantDataResult FPTR(Save)               (FTHIS(SQuantDataSeries), const TQuantDataSaveSettings* pSettings);
	EQuantDataResult FPTR(GetT1)              (FTHIS(SQuantDataSeries), TQuantDataT1s** ppData);
	EQuantDataResult FPTR(GetT2)              (FTHIS(SQuantDataSeries), TQuantDataT2s** ppData);
	EQuantDataResult FPTR(GetT6)              (FTHIS(SQuantDataSeries), TQuantDataT6s** ppData);
	EQuantDataResult FPTR(GetT8)              (FTHIS(SQuantDataSeries), TQuantDataT8s** ppData);
	EQuantDataResult FPTR(GetGtick)           (FTHIS(SQuantDataSeries), TQuantDataGtDataPoints** ppData);
	EQuantDataResult FPTR(SetT1)              (FTHIS(SQuantDataSeries), TQuantDataT1s* pData);
	EQuantDataResult FPTR(SetT2)              (FTHIS(SQuantDataSeries), TQuantDataT2s* pData);
	EQuantDataResult FPTR(SetT6)              (FTHIS(SQuantDataSeries), TQuantDataT6s* pData);
	EQuantDataResult FPTR(SetT8)              (FTHIS(SQuantDataSeries), TQuantDataT8s* pData);
	EQuantDataResult FPTR(SetGtick)           (FTHIS(SQuantDataSeries), TQuantDataGtDataPoints* pData);
	EQuantDataResult FPTR(Release)            (FTHIS(SQuantDataSeries));
};
ITYPE(SQuantDataSeries, IQuantDataSeries)

#ifdef __cplusplus
struct SQuantDataPeriods
{
	const TQuantDataPeriod* begin() { return Get(0); }
	const TQuantDataPeriod* end() { return Get(0) + Size(); }
	const TQuantDataPeriod* Get(TQuantDataSize index) { return m_functions.Get(this, index); }
	TQuantDataSize Size() { return m_functions.Size(this); }
	void Release() { return m_functions.Release(this); }
protected:
	~SQuantDataPeriods() {}
	typedef struct SQuantDataPeriodsFunctions TInterfaceFunctions;
	const TInterfaceFunctions m_functions ZERO_INIT;
};

struct SQuantDataSymbols
{
	const TQuantDataSymbolInfo* begin() { return Get(0); }
	const TQuantDataSymbolInfo* end() { return Get(0) + Size(); }
	const TQuantDataSymbolInfo* Get(TQuantDataSize index) { return m_functions.Get(this, index); }
	TQuantDataSize Size() { return m_functions.Size(this); }
	void Release() { return m_functions.Release(this); }
protected:
	~SQuantDataSymbols() {}
	typedef struct SQuantDataSymbolsFunctions TInterfaceFunctions;
	const TInterfaceFunctions m_functions ZERO_INIT;
};

struct SQuantDataSeries
{
	EQuantDataResult SetProvider(const TQuantDataProviderSettings* pSettings) {
		return m_functions.SetProvider(this, pSettings);
	}
	EQuantDataResult GetNativePeriods(IQuantDataPeriods** ppPeriods) {
		return m_functions.GetNativePeriods(this, ppPeriods);
	}
	EQuantDataResult GetSupportedSymbols(IQuantDataSymbols** ppSymbols, const TQuantDataSymbolsSettings* pSettings) {
		return m_functions.GetSupportedSymbols(this, ppSymbols, pSettings);
	}
	EQuantDataResult Download(const TQuantDataDownloadSettings* pSettings) {
		return m_functions.Download(this, pSettings);
	}
	EQuantDataResult Load(const TQuantDataLoadSettings* pSettings) {
		return m_functions.Load(this, pSettings);
	}
	EQuantDataResult Save(const TQuantDataSaveSettings* pSettings) {
		return m_functions.Save(this, pSettings);
	}
	EQuantDataResult GetT1(TQuantDataT1s** ppData) {
		return m_functions.GetT1(this, ppData);
	}
	EQuantDataResult GetT2(TQuantDataT2s** ppData) {
		return m_functions.GetT2(this, ppData); }
	EQuantDataResult GetT6(TQuantDataT6s** ppData) {
		return m_functions.GetT6(this, ppData);
	}
	EQuantDataResult GetT8(TQuantDataT8s** ppData) {
		return m_functions.GetT8(this, ppData);
	}
	EQuantDataResult GetGtick(TQuantDataGtDataPoints** ppData) {
		return m_functions.GetGtick(this, ppData);
	}
	EQuantDataResult SetT1(TQuantDataT1s* pData) {
		return m_functions.SetT1(this, pData);
	}
	EQuantDataResult SetT2(TQuantDataT2s* pData) {
		return m_functions.SetT2(this, pData);
	}
	EQuantDataResult SetT6(TQuantDataT6s* pData) {
		return m_functions.SetT6(this, pData);
	}
	EQuantDataResult SetT8(TQuantDataT8s* pData) {
		return m_functions.SetT8(this, pData);
	}
	EQuantDataResult SetGtick(TQuantDataGtDataPoints* pData) {
		return m_functions.SetGtick(this, pData);
	}
	EQuantDataResult Release() {
		return m_functions.Release(this);
	}
protected:
	~SQuantDataSeries() {}
	typedef struct SQuantDataSeriesFunctions TInterfaceFunctions;
	const TInterfaceFunctions m_functions ZERO_INIT;
};

#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

QUANTDATA_IMPORT_EXPORT EQuantDataResult QUANTDATA_CALL QuantData_CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#undef ZERO_INIT
#undef FTHIS
#undef FPTR
#undef ITYPE

#endif // I_QUANTDATA_H_
