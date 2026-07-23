#pragma once

//
//
// ---------------------------
// | MemoryMonitor以归档     |
// | 因AllocationEntry偏移量 |
// | 中size_t 是24偏移量     |
// | size_t应为8偏移量而非4  |
// | 此MemoryMonitor.c被归档 |
// --------------------------
//

// 因偏移量错误问题以无效
//-----------V-----------

/*
* 元提示
* MemoryMonitor是一个内存监控系统，提供了内存分配、释放、统计和垃圾回收等功能。
* 它可以帮助开发者跟踪内存使用情况，检测内存泄漏，并提供一些工具函数来管理内存。
* 高风险警告
* MemoryMonitor会记录所有通过它分配的内存，并且在释放时更新统计数据。
* 如果你直接使用标准的malloc/free而不是MemoryMonitor提供的mm_malloc/mm_free，那么这些内存将不会被监控，可能导致统计数据不准确，甚至无法检测到内存泄漏。
* 因此，建议你在整个程序中,尽量少使用标准分配函数，使用MemoryMonitor提供的API或MixinGC提供的API来分配和释放内存，以确保内存使用情况被正确监控和管理。
* 你可以用它来配合MixinGC来监控内存使用情况，并在必要时主动调用GC函数来回收内存，避免触发紧急GC。
*/

#include"Include.h"
#include"Boolean.h"
//#include"MixinGarbageCollection.h"

typedef struct {
    size_t totalAllocations;       // 分配次数
    size_t totalFrees;             // 释放次数
    size_t currentAllocations;     // 当前存活分配数
    size_t peakAllocations;        // 最大同时存活分配数
    size_t totalAllocatedBytes;    // 分配过的总字节数
    size_t totalFreedBytes;        // 已释放总字节数
    size_t currentAllocatedBytes;  // 当前存活字节数
    size_t peakAllocatedBytes;     // 峰值字节数
} MemoryStats;

typedef void (*MM_ITER_CB)(void* ptr, size_t size, double lastAccessTime, int collectable, void* user);

MixinRunTime_API void* mm_malloc(size_t size);
MixinRunTime_API void mm_free(void* ptr);

MixinRunTime_API void* mm_malloc_aligned(size_t size, size_t alignment);
//MixinRunTime_API void mm_free_aligned(void* ptr);

MixinRunTime_API MemoryStats mm_getStats(void);
MixinRunTime_API void mm_resetStats(int resetPeaks);    // 是否清零峰值要在实现中明确
MixinRunTime_API void mm_printStats(void);

MixinRunTime_API MemoryStats mm_getStats(void);

MixinRunTime_API void mm_dumpLeaks(void);

MixinRunTime_API void mm_setLargeAllocThreshold(size_t bytes);

MixinRunTime_API size_t mm_gc(double max_age_seconds, size_t min_size_to_free);

MixinRunTime_API void mm_iterateAllocations(MM_ITER_CB cb, void* user);

MixinRunTime_API int mm_touch(void* ptr);

MixinRunTime_API int mm_unmark_collectable(void* ptr);

MixinRunTime_API int mm_mark_collectable(void* ptr);

MixinRunTime_API void mm_free_safe(void** pptr);

MixinRunTime_API void mm_force_release_all(void);

//------------/\------------
//上面全部API以无效，已被归档