#pragma once

#include <__KCONF.h>
#include <Types.h>

typedef struct
{
    const char* Format;
    void**      Arguments;
    int         ArgumentIndex;
} LIB_FORMATTER_STATE;

typedef struct
{
    int LeftAlign;
    int ShowSign;
    int SpacePrefix;
    int AlternateForm;
    int ZeroPad;
    int Width;
    int Precision;
    int HasPrecision;
    int Length;
} LIB_FORMATTER_FLAGS;

/*Main*/
void KPrintf(const char*, ...);
// void KPrintfColor(uint32_t, uint32_t, const char*, ...);
void KFormatSpecifier(const char**, __builtin_va_list*);

/*Helpers*/
void HELP_PrintInteger(int, int, int);
void HELP_PrintUnsigned(uint32_t, int, int);
void HELP_PrintString(const char*);
void HELP_PrintChar(char);
void HELP_PrintPointer(void*);
int  HELP_StringLength(const char*);/*strlen???*/
void HELP_ReverseString(char*, int);
void HELP_IntegerToString(int, char*, int);
void HELP_UnsignedToString(uint32_t, char*, int);
void HELP_ProcessInteger(__builtin_va_list*, LIB_FORMATTER_FLAGS*, int, int);
void HELP_ProcessString(__builtin_va_list*, LIB_FORMATTER_FLAGS*);
void HELP_ProcessChar(__builtin_va_list*, LIB_FORMATTER_FLAGS*);
void HELP_ProcessPointer(__builtin_va_list* , LIB_FORMATTER_FLAGS*);
void HELP_FormatOutput(const char*, LIB_FORMATTER_FLAGS*, int, int);
void HELP_UnsignedToStringEx(uint64_t, char*, int, int);

/*Logging*/
void LOG_PError(const char*, ...);
void LOG_PWarn(const char*, ...);
void LOG_PInfo(const char*, ...);
void LOG_PDebug(const char*, ...);
void LOG_PSuccess(const char*, ...);