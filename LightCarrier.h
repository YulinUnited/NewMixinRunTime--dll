#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Include.h"
#include "Boolean.h"
#include "Util.h"
#include "MixinGarbageCollection.h"

    typedef struct {
        void(__cdecl* callback)(double currentTick, unsigned long frameIndex);
        double mainTick;
        double accumulatedTime;
        unsigned long frameIndex;
        void* lock;
        int isRunning;
    } NonBlockingState;

    struct LightCarrier {
        void* hWorker;
        void* hStopEvent;
        void* lock;
        volatile int running;
        void* frequency;
        double tickIntervalSec;
        void* callback;
        void* userData;
        void* baseTime;
        void* nextTick;
        int isNonBlocking;
    };

    typedef struct LightCarrier LightCarrier;

    typedef void(__cdecl* LCTickCallback)(double tickIntervalSec, void* userData);
    typedef void(__cdecl* TickCallback)(double tickIntervalSec);
    typedef void (*TickCallbacks)(double currentTick, unsigned long frameIndex);

    MixinRunTime_API LightCarrier* LC_Create(LCTickCallback cb, double tickIntervalSec, void* userData);
    MixinRunTime_API void LC_Destroy(LightCarrier* handle);
    MixinRunTime_API void LC_SetTickInterval(LightCarrier* handle, double tickIntervalSec);
    MixinRunTime_API double LC_GetTickInterval(LightCarrier* handle);
    MixinRunTime_API int LC_IsRunning(LightCarrier* handle);

    MixinRunTime_API int StartLightCarrierThread(TickCallback cb, double tickIntervalSec);
    MixinRunTime_API void StopLightCarrierThread(void);
    MixinRunTime_API void UpdateMainTick(double tickIntervalSec);

    MixinRunTime_API LightCarrier* LC_NonBlocking_Create(double mainTick, TickCallbacks callback);
    MixinRunTime_API void LC_NonBlocking_Destroy(LightCarrier* handle);
    MixinRunTime_API void LC_NonBlocking_Update(LightCarrier* handle, double deltaTime);
    MixinRunTime_API void LC_NonBlocking_SetMainTick(LightCarrier* handle, double newTick);

#ifdef __cplusplus
}
#endif