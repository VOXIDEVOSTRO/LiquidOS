#include <Errors.h>

/*Local*/
#include <Externals/Formatter.h>
#include <Externals/Emmiter.h>

void
LOG_PError(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[    ERROR    ]: ");

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

    PutString("[   WARNING   ]: ");

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

    PutString("[ INFORMATION ]: ");

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

    PutString("[   SUCCESS   ]: ");

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