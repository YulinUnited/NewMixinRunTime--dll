#pragma once


#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include <float.h>
#include <basetsd.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/mman.h>
#endif

#include <inttypes.h>
#include <sysinfoapi.h>
#include <vcruntime.h>
#include <wchar.h>
#include <winnt.h>
#include <tlhelp32.h>
#include <winternl.h>


#include <assert.h>
#include <mmsystem.h>
#include <stdbool.h>

#include <ctype.h>

#include "MixinLog.h"


#ifndef MixinRunTime_API_H
#define MixinRunTime_API_H

#if defined(_WIN32)|| defined(_WIN64)
#ifdef MixinRunTime_EXPORTS
#define MixinRunTime_API __declspec(dllexport)
#else
#define MixinRunTime_API __declspec(dllimport)
#endif
#else
#define MixinRunTime_API
#endif

#endif // !MixinRunTime_API_H