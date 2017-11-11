
#ifndef I_QUANTDATA_H
#define I_QUANTDATA_H

#define QUANTDATA_EXPORT __declspec(dllexport)
#define QUANTDATA_IMPORT __declspec(dllimport)
#define QUANTDATA_CALL __cdecl

#ifdef QUANTDATA_DLL
#ifdef QUANTDATA_IMPL
#define QUANTDATA_IMPORT_OR_EXPORT QUANTDATA_EXPORT
#else
#define QUANTDATA_IMPORT_OR_EXPORT QUANTDATA_IMPORT
#endif
#else
#define QUANTDATA_IMPORT_OR_EXPORT
#endif


#ifdef __cplusplus
extern "C" {
#endif

QUANTDATA_IMPORT_OR_EXPORT void QUANTDATA_CALL DownloadTimeSeries();

#ifdef __cplusplus
}
#endif

#endif // I_QUANTDATA_H
