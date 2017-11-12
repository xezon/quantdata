
#ifndef INTTYPES_H
#define INTTYPES_H

#ifdef ZORRO_LITE_C

typedef char           int8_t;
typedef short          int16_t;
typedef int            int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

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

#include <stdint.h>

#endif

#endif // INTTYPES_H
