/*Configs*/
#include <__LCONF.h>

/*Libraries*/
#include <Externals/Formatter.h>

#ifdef M_DEBUGS
    #define M_PDebug(Format, ...) \
        LOG_PDebug(Format, ##__VA_ARGS__)
#else
    #define M_PDebug(Format, ...) \
        do {} while (0)
#endif

#ifdef M_ERRORS
    #define M_PError(Format, ...) \
        LOG_PError(Format, ##__VA_ARGS__)
#else
    #define M_PError(Format, ...) \
        do {} while (0)
#endif

#ifdef M_INFORMATIONS
    #define M_PInfo(Format, ...) \
        LOG_PInfo(Format, ##__VA_ARGS__)
#else
    #define M_PInfo(Format, ...) \
        do {} while (0)
#endif

#ifdef M_WARNS
    #define M_PWarn(Format, ...) \
        LOG_PWarn(Format, ##__VA_ARGS__)
#else
    #define M_PWarn(Format, ...) \
        do {} while (0)
#endif

#ifdef M_SUCCESSES
    #define M_PSuccess(Format, ...) \
        LOG_PSuccess(Format, ##__VA_ARGS__)
#else
    #define M_PSuccess(Format, ...) \
        do {} while (0)
#endif
