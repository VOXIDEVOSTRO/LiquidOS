#include <Errors.h>

/*Local*/
#include <Externals/Formatter.h>
#include <Externals/Emmiter.h>
#include <Externals/DefaultColors.h>
#include <Externals/Console.h>

void
LOG_PError(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[");
    SetBackgroundColor(ClrError, ClrInvisible);
    PutString("    ERROR    ");
    SetBackgroundColor(ClrNormal, ClrInvisible);
    PutString("]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            KFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}

void
LOG_PWarn(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[");
    SetBackgroundColor(ClrWarn, ClrInvisible);
    PutString("   WARNING   ");
    SetBackgroundColor(ClrNormal, ClrInvisible);
    PutString("]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            KFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}

void
LOG_PInfo(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[");
    SetBackgroundColor(ClrInfo, ClrInvisible);
    PutString(" INFORMATION ");
    SetBackgroundColor(ClrNormal, ClrInvisible);
    PutString("]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            KFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}

void
LOG_PDebug(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    SetBackgroundColor(ClrDebug, ClrInvisible);
    PutString("[    DEBUG    ]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            KFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}

void
LOG_PSuccess(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[");
    SetBackgroundColor(ClrSuccess, ClrInvisible);
    PutString("   SUCCESS   ");
    SetBackgroundColor(ClrNormal, ClrInvisible);
    PutString("]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            KFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}