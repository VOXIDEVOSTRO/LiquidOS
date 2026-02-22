#pragma once

#include <Types.h>

#include <__LCONF.h>

/*F016*/
#ifdef __F16
    #define FontW 8
    #define FontH 16
#endif

extern const uint8_t TerminusFont[MaxFontEntries][MaxFontMap];

void DisplayChar(uint32_t*, uint32_t, uint32_t, uint32_t, char, uint32_t);
void DisplayString(uint32_t*, uint32_t, uint32_t, uint32_t, const char*, uint32_t);