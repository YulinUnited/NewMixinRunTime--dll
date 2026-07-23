#pragma once
#include "Include.h"
#include "Boolean.h"

// 最大可分配 1GB
#define MAX_MEMORY_LIMIT (1024ULL * 1024ULL * 1024ULL)


// ================= 带锁版本 =================
MixinRunTime_API int   LockedMemoryManager_Init();
MixinRunTime_API void  LockedMemoryManager_Destroy();
MixinRunTime_API void* LockedMemoryManager_Alloc(size_t size);
MixinRunTime_API void  LockedMemoryManager_Free(void* ptr);
MixinRunTime_API int   LockedMemoryManager_SetLimit(size_t size); // 限制总大小，<=1GB
MixinRunTime_API size_t LockedMemoryManager_GetUsed();

// ================= 无锁版本 =================
MixinRunTime_API int   UnlockedMemoryManager_Init();
MixinRunTime_API void  UnlockedMemoryManager_Destroy();
MixinRunTime_API void* UnlockedMemoryManager_Alloc(size_t size);
MixinRunTime_API void  UnlockedMemoryManager_Free(void* ptr);
MixinRunTime_API int   UnlockedMemoryManager_SetLimit(size_t size); // 限制总大小，<=1GB
MixinRunTime_API size_t UnlockedMemoryManager_GetUsed();
