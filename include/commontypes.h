
#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#ifdef ZORRO_LITE_C

typedef char           int8_t;
typedef short          int16_t;
typedef int            int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned int   size_t;

typedef struct sint64
{
	uint32_t lo;
	int32_t hi;
} int64_t;

typedef struct uint64
{
	uint32_t lo;
	uint32_t hi;
} uint64_t;

#else

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#endif // __cplusplus

typedef void* (__cdecl* alloc_func)(size_t size);
typedef void  (__cdecl* free_func )(void* p);

#endif // ZORRO_LITE_C

#endif // COMMONTYPES_H
