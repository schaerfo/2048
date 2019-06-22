#ifndef BOOL_H
#define BOOL_H

#ifdef __m68k__
#define bool unsigned short
#define true 1
#define false 0
#else
#include <stdbool.h>
#endif

#endif
