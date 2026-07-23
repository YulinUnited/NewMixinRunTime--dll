这是NewMixinRunTime.dll及其包含的头文件，在使用时请一定注意：部分内容尚未经过测试，建议在工程里面优先建立一个Demo进行测试确保各个模块皆能使用；
译：
This is the NewMixinRunTime.dll and its included header files. Please note when using it: some parts haven't been tested yet, so it's recommended to first create a demo in your project to test and make sure all modules work.

【由于部分内容尚未完成测试，目前只提供MixinGarbageCollection的文档，至少暂时以README.md 这种方式展示出来/Since some parts haven't finished testing yet, currently we only provide documentation for MixinGarbageCollection, at least for now it's shown in README.md】

# MixinGC 垃圾回收系统头文件 / MixinGC Garbage Collection Header

## 概述 / Overview

`MixinGC.h` 定义了 Mixin 运行时的垃圾回收（GC）子系统，提供内存分配、显式回收、GC 策略控制、统计、弹性调优以及紧急安全机制。所有 API 均以 `MixinGC_` 前缀导出，开发者可通过这些接口主动管理内存，避免触发不可逆的系统保护。

`MixinGC.h` defines the garbage collection (GC) subsystem of the Mixin runtime, offering memory allocation, explicit reclamation, GC policy control, statistics, elastic tuning, and an emergency safety mechanism. All APIs are exported with the `MixinGC_` prefix. Developers can actively manage memory through these interfaces to avoid triggering the irreversible system protection.

---

## 🚨 高风险警告 / High‑Risk Warning

MixinGC 拥有一个绝对的、不容践踏的底线：当物理内存极度不足、即将抛出 `OutOfMemoryError` 时，MixinGC 会**彻底接管全部权限**，阻止一切回收内存的尝试，并**无条件摧毁整个运行时**。你的程序将立即崩溃，无法继续运行。它以运行时和程序为代价，换取操作系统级别的安全，防止系统被拖垮。

该机制被称为 **True_Emergency_GC**，仅在系统物理内存极度不足时触发。一旦触发，运行时将永久终止，除非重启。

MixinGC has an absolute, inviolable bottom line: when physical memory is critically low and an `OutOfMemoryError` is imminent, MixinGC **completely seizes all permissions**, prevents any memory reclamation attempt, and **unconditionally destroys the entire runtime**. Your program will crash immediately and cannot continue. It sacrifices the runtime and your code to ensure operating‑system‑level safety, preventing the system from being dragged down.

This mechanism is named **True_Emergency_GC**, triggering only when system physical memory is extremely scarce. Once triggered, the runtime is permanently terminated unless restarted.

**重要建议 / Important Recommendations:**
- 永远不要依赖紧急 GC 来管理内存，它只是最后一道防线。  
  Never rely on the emergency GC for memory management; it is only the last line of defense.
- 请合理设置运行时内存上限，并主动使用 `MixinGC_CollectNow`、`MixinGC_StartPeriodicCollector` 等函数进行回收。  
  Set a reasonable heap limit and proactively call functions like `MixinGC_CollectNow`, `MixinGC_StartPeriodicCollector` to reclaim memory.
- 最佳实践是配合 `MemoryMonitor` 监控系统内存，在压力升高时主动调用 GC，避免触及底线。  
  Best practice is to use a `MemoryMonitor` to watch system memory and actively invoke GC when pressure rises, thus avoiding the bottom line.

---

## 常量 / Constants

| 常量 / Constant | 值 / Value | 说明 / Description |
|----------------|------------|-------------------|
| `GC_True` | `True` | 逻辑真 / logical true |
| `GC_False` | `False` | 逻辑假 / logical false |
| `HANDLE_INVALID` | `0u` | 无效句柄值 / invalid handle value |
| `MAX_HEAP_LIMIT` | `3 * 1024 * 1024 * 1024` (3 GB) | 最大堆上限 / maximum heap limit |
| `MB(x)` | `((size_t)(x) * 1024 * 1024)` | 兆字节转换宏 / megabyte conversion macro |
| `LARGE_THRESHOLD` | `64 * 1024` (64 KB) | 大对象阈值 / large object threshold |

---

## 类型 / Types

```c
typedef uint32_t GCHandle;                       // GC 句柄 / GC handle

typedef struct {
    size_t total_allocated_bytes;                // 已分配总字节数 / total allocated bytes
    size_t freed_bytes;                          // 上次 GC 释放字节数 / bytes freed by last GC
    uint64_t gc_count;                           // GC 运行总次数 / total GC runs
    double last_gc_seconds;                      // 上次 GC 耗时（秒） / last GC duration (seconds)
    size_t live_object_count;                    // 存活对象数 / live object count
    size_t live_entity_count;                    // 存活实体数 / live entity count
} MixinGCStats;                                  // GC 统计信息 / GC statistics

[分配标志与GC策略目前还有一些小问题/There are still a few minor issues with allocation flags and the GC strategy.]

GC_STRATEGY_AGGRESSIVE	积极回收 / aggressive
GC_STRATEGY_BALANCED	平衡回收 / balanced
GC_STRATEGY_CONSERVATIVE	保守回收 / conservative
GC_STRATEGY_DEFERRED	延迟回收 / deferred
GC_STRATEGY_CUSTOM	自定义 / custom
GC_STRATEGY_IMMEDIATELY	立即回收 / immediate

MixinAllocFlags – 分配标志 / Allocation Flags

标志 / Flag	值 / Value	说明 / Description
MIXIN_ALLOC_NONE	0	无标志 / no flag
MIXIN_ALLOC_ZERO	1 << 0	分配后清零 / zero memory
MIXIN_ALLOC_NO_GC	1 << 1	禁止触发 GC / prevent GC
MIXIN_ALLOC_GC_TRACKED	1 << 2	GC 追踪 / GC tracked
MIXIN_ALLOC_FIXED	1 << 3	固定地址 / fixed address
MIXIN_ALLOC_INTERNAL	1 << 4	内部使用 / internal use



API 分类 / API Categories

1. 初始化和关闭 / Initialization & Shutdown
函数 / Function	说明 / Description
Boolean MixinGC_Init(size_t initial_handle_capacity)	初始化 GC 系统 / initialize GC system
void MixinGC_Shutdown(void)	关闭 GC 系统 / shutdown GC system

2. 内存分配和释放 / Memory Allocation & Deallocation
函数 / Function	说明 / Description
void* MixinGC_Allocate(size_t size)	分配内存 / allocate memory
void* MixinGC_AllocateEx(size_t size, MixinAllocFlags flags)	带标志分配 / allocate with flags
void MixinGC_Free(void* payload)	释放内存 / free memory
void MixinGC_FreeEx(void* ptr)	扩展释放 / extended free
void* MixinGC_Calloc(size_t count, size_t size)	分配并清零 / allocate and zero
void* MixinGC_Realloc(void* ptr, size_t new_size)	重新分配 / reallocate
void* Mixin_Realloc_Ex(void* payload, size_t new_size)	扩展重新分配 / extended realloc
size_t MixinGC_Msize(void* payload)	获取可用大小 / get usable size
size_t MixinGC_Get_Alloc_Size(void* payload)	获取实际分配大小 / get actual allocation size
对齐分配系列 / Aligned Allocation Series：

函数 / Function	说明 / Description
void MixinGC_Aligned_Free(void* payload)	对齐释放 / aligned free
void* MixinGC_Aligned_Realloc(void* payload, size_t new_size, size_t alignment)	对齐重新分配 / aligned realloc
void* MixinGC_Aligned_Recalloc(...)	对齐重新分配并清零 / aligned recalloc
size_t MixinGC_Aligned_Msize(void* payload, size_t alignment, size_t offset)	对齐块可用大小 / aligned usable size
（其他 Aligned_Offset_* 函数支持额外偏移）	
操作系统级分配 / OS‑level Allocation：

函数 / Function	说明 / Description
void* MixinGC_OperatingSystemAllocate(size_t size)	直接向 OS 申请内存
void MixinGC_OperatingSystemFree(void* ptr, size_t size)	直接向 OS 释放内存

3. 实体和句柄管理 / Entity & Handle Management
函数 / Function	说明 / Description
GCHandle MixinGC_CreateHandle(void* payload, void* raw)	创建 GC 句柄
GCHandle MixinGC_CreateEntityHandle(void* payload, void* raw)	创建实体句柄
void* MixinGC_HandleToPtr(GCHandle h)	句柄转指针
void MixinGC_DestroyHandle(GCHandle h)	销毁句柄
void* MixinGC_AllocateEntity(size_t payloads, int id, MixinAllocFlags flags)	分配实体
void MixinGC_Entity_Free(void* payload)	释放实体
void MixinGC_RegisterRoot(GCHandle h)	注册根对象
void MixinGC_UnregisterRoot(GCHandle h)	取消根注册

4. GC 控制和统计 / GC Control & Statistics
函数 / Function	说明 / Description
void MixinGC_CollectNow(void)	立即触发完整 GC
int MixinGC_StartPeriodicCollector(unsigned int interval_seconds)	启动周期性 GC
void MixinGC_StopPeriodicCollector(void)	停止周期性 GC
size_t MixinGC_PredictReclaimable(void)	预估可回收字节数
MixinGCStats MixinGC_GetStats(void)	获取 GC 统计信息
void MixinGC_SetOnCollectCallback(MixinGC_OnCollect cb)	设置 GC 后回调
int Get_GC_PeriodicCollector(void)	查询周期性 GC 状态
void Set_GC_PeriodicCollector(unsigned int interval_seconds)	设置并启动周期性 GC

5. 弹性调优 / Elastic Tuning
函数 / Function	说明 / Description
void MixinGC_SetHeapLimit(size_t bytes)	设置堆上限
void MixinGC_SetElasticThreshold(double ratio)	设置弹性阈值 (0~1)
void MixinGC_CollectIncremental(int steps)	增量 GC
int elastic_should_trigger(void)	检查弹性触发条件

6. 辅助函数 / Helper Functions
函数 / Function	说明 / Description
int is_Object(void* payload)	检查是否为对象
int is_Entity(void* payload)	检查是否为实体
Object* MixinGC_GetObjectPtr(void)	获取内部对象指针
Entity* MixinGC_GetEntityPtr(void)	获取内部实体指针
int should_trigger_predictive_gc(void)	预测性 GC 判断
void MixinGC_DebugDump(void)	调试输出


内联判断 / Inline Helpers：

static inline Boolean ShouldCollect(const Object* e)      // 根据 isRemove 判断
static inline Boolean ShouldCollectEntity(const Entity* e) // 根据 forceDead 判断


使用步骤 / Usage Steps
包含头文件 / Include Header

c
#include <MixinGarbageCollection.h>

1.链接库 / Link Library
链接 MixinRunTime.lib，确保运行时能找到 MixinRunTime.dll。
Link against MixinRunTime.lib and ensure MixinRunTime.dll is accessible at runtime.

2.初始化 / Initialize
在程序入口处调用 MixinGC_Init，并可选配置堆上限和弹性阈值。
Call MixinGC_Init at startup; optionally configure heap limit and elastic threshold.

3.使用 GC 分配器 / Use GC Allocators
使用 MixinGC_Allocate, MixinGC_Free, MixinGC_Calloc 等管理内存，或使用被 GC 替换的标准分配函数。
Manage memory using MixinGC_Allocate, MixinGC_Free, MixinGC_Calloc etc., or the GC‑aware standard allocators.

4.主动回收 / Proactive Collection
调用 MixinGC_CollectNow() 手动回收，或 MixinGC_StartPeriodicCollector() 开启自动周期回收。
Call MixinGC_CollectNow() for manual collection, or MixinGC_StartPeriodicCollector() for periodic background collection.

5.结束 / Shutdown
程序退出前调用 MixinGC_Shutdown()。
Call MixinGC_Shutdown() before exit.


简单示例 / Quick Example
c
#include "MixinGC.h"

int main() {
    if (MixinGC_Init(1024) != GC_True) return -1;

    MixinGC_SetHeapLimit(MB(512));         // 512 MB 堆上限 / heap limit
    MixinGC_SetElasticThreshold(0.75);     // 75% 触发弹性 GC / elastic GC at 75%

    void* buf = MixinGC_Allocate(1024);
    // ... use buf ...
    MixinGC_Free(buf);

    MixinGC_CollectNow();                  // 手动触发 GC / manual GC
    MixinGC_StartPeriodicCollector(30);    // 每 30 秒周期回收 / periodic every 30s

    // ... application logic ...

    MixinGC_Shutdown();
    return 0;
}


注意事项 / Notes
绝对不要依赖 True_Emergency_GC 进行常规内存管理，它仅在灾难性内存耗尽时摧毁一切。请主动管理内存。
Never rely on True_Emergency_GC for regular memory management; it destroys everything on catastrophic exhaustion. Proactively manage memory.

多线程环境下 GC 接口通常是线程安全的，但请结合具体实现确认。
GC interfaces are generally thread‑safe in multi‑threaded environments, but verify with the specific implementation.

对齐分配必须使用对应的对齐释放函数（例如 MixinGC_Aligned_Free）。
Aligned allocations must be freed with the corresponding aligned deallocation function (e.g., MixinGC_Aligned_Free).

根对象注册可防止被 GC 错误回收，跨 DLL 使用时请确保句柄有效。
Root registration prevents erroneous collection; ensure handles are valid when used across DLL boundaries.

你必须保证，永远不要逼迫MixinGarbageCollection激活这道防线！/You have to make sure to never force MixinGarbageCollection to activate this defense line!
