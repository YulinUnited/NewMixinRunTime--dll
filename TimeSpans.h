#pragma once

#include "Include.h"

#define TS_CDECL __cdecl

// callback: native -> managed (tick seconds, frame index, userData)
typedef void (TS_CDECL* TS_TickCB)(double tickSec, uint64_t frameIndex, void* userData);

// Initialize the TimeSpans engine (non-blocking, driven by Update)
// mainTickSec: target interval in seconds (>0).
// returns 0 on success, negative on error.
MixinRunTime_API int TS_CDECL TS_Init(double mainTickSec);

// Add a callback. returns a 64-bit id (>0) you can use to remove.
// cb: function pointer, userData: any pointer (e.g. IntPtr from GCHandle), priority: higher value => earlier call
MixinRunTime_API uint64_t TS_CDECL TS_AddCallback(TS_TickCB cb, void* userData, int priority);

// Remove callback by id. safe to call even if id not exist.
MixinRunTime_API void TS_CDECL TS_RemoveCallback(uint64_t id);

// Called every main loop with elapsed seconds; non-blocking.
// Internally will dispatch callbacks when accumulated >= mainTick.
MixinRunTime_API void TS_CDECL TS_Update(double deltaTimeSec);

// Change main tick interval at runtime (>0)
MixinRunTime_API void TS_CDECL TS_SetMainTick(double mainTickSec);

// Stops and cleans internal state.
MixinRunTime_API void TS_CDECL TS_Stop(void);

// Get current frame index (monotonic)
MixinRunTime_API uint64_t TS_CDECL TS_GetFrameIndex(void);

// Version (Major<<16 | Minor)
MixinRunTime_API uint32_t TS_CDECL TS_GetVersion(void);

