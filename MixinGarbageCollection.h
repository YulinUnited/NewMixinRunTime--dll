#pragma once
/*
* 元提示：这是一个垃圾回收系统的头文件，提供了GC的初始化、内存分配、GC控制和统计等功能。
*它定义了GC句柄、GC策略、分配标志以及相关的API函数。用户可以通过这些API来管理内存和控制GC行为。
* 高风险警告：
* MixinGC拥有一个绝对的、不容践踏的底线，如果你失误了导致物理内存不足，即将丢出OutOfMemoryError时，MixinGC会彻底接管全部的权限，阻止你的一切任何试图回收内存的操作方式
* 它会无条件的摧毁整个运行时，将你的代码彻底毁掉，虽然你在编译器方面可能不会有任何异常，但是你的程序一运行会立刻崩溃，无法再继续运行，它以整个运行时与你的代码程序作为代价换取系统安全
* 这个设计是为了保护你的系统不被你的程序拖垮，而不是保护你的程序不被拖垮，所以请务必合理设置运行时内存大小，避免触发这个底线
* 它被命名为True_Emergency_GC，顾名思义，它是一个真正的紧急GC，只有在系统内存极度不足时才会触发，并且一旦触发就会彻底摧毁运行时，运行时无法再继续运行，除非重启运行时或重新开启运行时
* 但是，核武器如果不被管制也是十分无解的，因此提供了许多建议甚至十分支持开发者手动调用管理的函数
* 这些函数例如：MixinGC_CollectNow、MixinGC_StartPeriodicCollector、MixinGC_StopPeriodicCollector等函数，可以让你更主动的控制GC的行为，避免触发紧急GC
* 紧急垃圾回收策略它不是一个正常的GC策略，它是一个最后的底线，只有在系统物理内存极度不足时才会触发，所以建议所有的开发者不应该也不能依赖它来管理内存，应该合理设置运行时内存大小，并且在必要时主动调用GC函数来回收内存
* 最佳搭配的方案也是最为推荐的方案是使用MemoryMonitor来监控系统内存使用情况，并且在内存使用过高时主动调用GC函数来回收内存，避免触发紧急GC
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Include.h"
#include "Object.h"
#include "Boolean.h"
#include "Entity.h"

#define GC_True True
#define GC_False False

    typedef uint32_t GCHandle;

#define HANDLE_INVALID 0u
#define MAX_HEAP_LIMIT (3ULL*1024*1024*1024)//上限3GB，最大
#define MB(x) ((size_t)(x) * 1024 * 1024)

#define LARGE_THRESHOLD (64 * 1024)

    typedef struct {
        size_t total_allocated_bytes; // 目标堆中分配的总字节数
        size_t freed_bytes;           // 目标是否满足上次GC释放的字节数
        uint64_t gc_count;            // 目标的GC运行总次数
        double last_gc_seconds;       // 是否满足上次GC运行的持续时间（以秒为单位）
        size_t live_object_count;
        size_t live_entity_count;
    } MixinGCStats;

    /*
        * GarbageCollection策略枚举
        */
    typedef enum {
        GC_STRATEGY_AGGRESSIVE,//积极回收
        GC_STRATEGY_BALANCED,//平衡回收
        GC_STRATEGY_CONSERVATIVE,//保守回收
        GC_STRATEGY_DEFERRED,//延迟回收
        GC_STRATEGY_CUSTOM,//自定义回收
        GC_STRATEGY_IMMEDIATELY//立即回收
    } GCStrategy;

    typedef enum MixinAllocFlags {
        MIXIN_ALLOC_NONE = 0,
        MIXIN_ALLOC_ZERO = 1 << 0,
        MIXIN_ALLOC_NO_GC = 1 << 1,
        MIXIN_ALLOC_GC_TRACKED = 1 << 2,
        MIXIN_ALLOC_FIXED = 1 << 3,
        MIXIN_ALLOC_INTERNAL = 1 << 4,
    } MixinAllocFlags;

    extern Boolean g_runtime_dead;
    extern Boolean g_running;

    MixinRunTime_API void* MixinGC_AllocateEx(size_t size, MixinAllocFlags flags);

    MixinRunTime_API void MixinGC_FreeEx(void* ptr);


    MixinRunTime_API void* Mixin_Realloc_Array(void* old_ptr, size_t old_count, size_t new_count, size_t elem_size);

    MixinRunTime_API size_t MixinGC_Get_Alloc_Size(void* payload);


    MixinRunTime_API void MixinGC_OperatingSystemFree(void* ptr, size_t size);
    MixinRunTime_API void* MixinGC_OperatingSystemAllocate(size_t size);


    MixinRunTime_API void* Mixin_Realloc_Ex(void* payload, size_t new_size);

    MixinRunTime_API void* MixinGC_Calloc(size_t count, size_t size);

    MixinRunTime_API void* MixinGC_Realloc(void* ptr, size_t new_size);

    MixinRunTime_API size_t MixinGC_Msize(void* payload);


    MixinRunTime_API void MixinGC_Unknown_Memory_Free(void* unknown);


    MixinRunTime_API void MixinGC_Aligned_Free(void* payload);

    MixinRunTime_API void* MixinGC_Aligned_Realloc(void* payload, size_t new_size, size_t alignment);

    MixinRunTime_API void* MixinGC_Aligned_Offset_Realloc(void* payload, size_t new_size, size_t alignment, size_t offset);

    MixinRunTime_API void* MixinGC_Aligned_Recalloc(void* payload, size_t count, size_t size, size_t alignment);

    MixinRunTime_API void* MixinGC_Aligned_Offset_Recalloc(void* payload, size_t count, size_t size, size_t alignment, size_t offset);

    MixinRunTime_API size_t MixinGC_Aligned_Msize(void* payload, size_t alignment, size_t offset);

    MixinRunTime_API void MixinGC_Free_Base(void* payload);

    MixinRunTime_API void* MixinGC_Calloc_Base(size_t count, size_t size);

    MixinRunTime_API void* MixinGC_Realloc_Base(void* payload, size_t new_size);

    MixinRunTime_API void* MixinGC_Recalloc_Base(void* payload, size_t count, size_t size);

    MixinRunTime_API void* MixinGC_Recalloc_(void* payload, size_t count, size_t size);

    MixinRunTime_API int MixinGC_Callnewh(size_t size);

    MixinRunTime_API void* MixinGC_Expand(void* payload, size_t new_size);



    /* API surface; */
    //启动和关闭GC系统
    MixinRunTime_API Boolean MixinGC_Init(size_t initial_handle_capacity);

    MixinRunTime_API void MixinGC_Shutdown(void);

    MixinRunTime_API Object* MixinGC_GetObjectPtr();

    MixinRunTime_API Entity* MixinGC_GetEntityPtr();


    //内存分配和释放
    MixinRunTime_API void* MixinGC_Allocate(size_t size);

    MixinRunTime_API void  MixinGC_Free(void* payload);


    MixinRunTime_API GCHandle MixinGC_CreateEntityHandle(void* payload, void* raw);

    MixinRunTime_API void* MixinGC_AllocateEntity(size_t payloads, int id, MixinAllocFlags mixinallocflags);

    MixinRunTime_API void MixinGC_Entity_Free(void* payload);


    //GC句柄管理
    MixinRunTime_API GCHandle MixinGC_CreateHandle(void* payload, void* raw);

    MixinRunTime_API void* MixinGC_HandleToPtr(GCHandle h);

    MixinRunTime_API void  MixinGC_DestroyHandle(GCHandle h);


    //分配根对象
    MixinRunTime_API void MixinGC_RegisterRoot(GCHandle h);

    MixinRunTime_API void MixinGC_UnregisterRoot(GCHandle h);


    // GC控制和统计
    MixinRunTime_API void MixinGC_CollectNow(void);

    MixinRunTime_API int  MixinGC_StartPeriodicCollector(unsigned int interval_seconds);

    MixinRunTime_API void MixinGC_StopPeriodicCollector(void);


    //将预估可回收内存大小返回给调用者
    MixinRunTime_API size_t MixinGC_PredictReclaimable(void);

    MixinRunTime_API MixinGCStats MixinGC_GetStats(void);


    // GC回调函数类型和注册
    typedef void (*MixinGC_OnCollect)(const MixinGCStats*);

    MixinRunTime_API void MixinGC_SetOnCollectCallback(MixinGC_OnCollect cb);


    //获取和设置周期性收集器的时间间隔
    MixinRunTime_API int Get_GC_PeriodicCollector(void);

    MixinRunTime_API void Set_GC_PeriodicCollector(unsigned int interval_seconds);


    /* Elastic GC tuning APIs */
    //设置堆内存限制和弹性阈值
    MixinRunTime_API void MixinGC_SetHeapLimit(size_t bytes); /* total heap cap for pressure calc */

    MixinRunTime_API void MixinGC_SetElasticThreshold(double ratio); /* 0..1 */

    MixinRunTime_API void MixinGC_CollectIncremental(int steps);

    /* Business hook helpers:
       Default implementations provided in .c (safe stubs).
       If your payload layout differs, replace these functions in your build.
    */
    //是否是对象的检查和提取函数
    MixinRunTime_API int is_Object(void* payload);
    MixinRunTime_API int is_Entity(void* payload);

    MixinRunTime_API int should_trigger_predictive_gc(void);

    MixinRunTime_API void MixinGC_DebugDump();
    MixinRunTime_API int elastic_should_trigger(void);

    static inline Boolean ShouldCollect(const Object* e) 
    {
        if (!e) { return GC_False; }
        
        return e->isRemove == GC_True;
    }
    //是否是实体类
    static inline Boolean ShouldCollectEntity(const Entity* entite)
    {
        if (!entite)
        {
            return GC_False;
        }
        return entite->forceDead == GC_True;
    }

    static inline size_t max_size(size_t a, size_t b)
    {
        return a > b ? a : b;
    }

#ifdef __cplusplus
}
#endif