#pragma once

#include <__KCONF.h>

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
void KrnPrintf(const char*, ...);
// void KrnPrintfColor(uint32_t, uint32_t, const char*, ...);
void ProcessFormatSpecifier(const char**, __builtin_va_list*);

/*Helpers*/
void PrintInteger(int, int, int);
void PrintUnsigned(uint32_t, int, int);
void PrintString(const char*);
void PrintChar(char);
void PrintPointer(void*);
int  StringLength(const char*);
void ReverseString(char*, int);
void IntegerToString(int, char*, int);
void UnsignedToString(uint32_t, char*, int);
void _ProcessInteger(__builtin_va_list*, LIB_FORMATTER_FLAGS*, int, int);
void _ProcessString(__builtin_va_list*, LIB_FORMATTER_FLAGS*);
void _ProcessChar(__builtin_va_list*, LIB_FORMATTER_FLAGS*);
void _ProcessPointer(__builtin_va_list* , LIB_FORMATTER_FLAGS*);
void _FormatOutput(const char*, LIB_FORMATTER_FLAGS*, int, int);
void UnsignedToStringEx(uint64_t, char*, int, int);

/*Logging*/
void PError(const char*, ...);
void PWarn(const char*, ...);
void PInfo(const char*, ...);
void _PDebug(const char*, ...);
void PSuccess(const char*, ...);