#pragma once
#ifndef MIXIN_LOG_H
#define MIXIN_LOG_H

#include "Include.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum
    {
        LOG_INFO,
        LOG_WARNING,
        LOG_ERROR,
        LOG_DEBUG
    } LogLevel;

    void Runtime_Log(LogLevel level, const char* fmt, ...);

#define Log(fmt,...) \
    Runtime_Log(LOG_INFO,fmt,##__VA_ARGS__)

#define LogWarning(fmt,...) \
    Runtime_Log(LOG_WARNING,fmt,##__VA_ARGS__)

#define LogError(fmt,...) \
    Runtime_Log(LOG_ERROR,fmt,##__VA_ARGS__)

#define LogDebug(fmt,...) \
    Runtime_Log(LOG_DEBUG,fmt,##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif

