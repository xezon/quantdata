
#ifndef INTTYPES_H
#define INTTYPES_H

#ifdef ZORRO_LITE_C

struct longlong
{
	unsigned long lo;
	long hi;
};

struct ulonglong
{
	unsigned long lo;
	unsigned long hi;
};

typedef char           int8_t;
typedef short          int16_t;
typedef int            int32_t;
typedef longlong       int64_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef ulonglong      uint64_t;

#else

#include <stdint.h>

#endif

#endif // INTTYPES_H
