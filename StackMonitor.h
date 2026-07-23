#pragma once
#include "Include.h"
#include "Util.h"
//声明到头文件中
	// -------- 配置与限制 --------
#define MAX_ENTRIES 1024
#define FAST_FAIL_STACK_BUFFER_OVERRUN 4

	/*typedef struct _CLIENT_ID {
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	} CLIENT_ID, * PCLIENT_ID;*/
	// 溢出回调：pid, tid, usedBytes, thresholdBytes
typedef void (*CSM_OverflowHandler)(DWORD pid, DWORD tid, size_t usedBytes, size_t thresholdBytes);

static DWORD g_pollIntervalMs = 50;      // 检查已注册线程的频率
static DWORD g_defaultEnumIntervalMs = 1000; // 自动注册枚举间隔

// -------- 内部数据结构 --------
typedef struct {
	DWORD pid;
	DWORD tid;
	size_t thresholdBytes;
	size_t stackBase;
	size_t stackLimit;
	int haveStackLimits; // 0/1
	int active;          // 0/1
} Entry;

static Entry g_entries[MAX_ENTRIES];
static CRITICAL_SECTION g_cs;
static HANDLE g_thread = NULL;
static HANDLE g_stopEvent = NULL;

static int g_autoRegister = 0;
static size_t g_autoDefaultThreshold = 64 * 1024; // 默认 64KB
static DWORD g_autoEnumIntervalMs = 1000;

static CSM_OverflowHandler g_handler = NULL;

// --------- NT API 原型 (动态调用) ----------
typedef LONG NTSTATUS;
typedef NTSTATUS(NTAPI* PFN_NtQueryInformationThread)(
	HANDLE ThreadHandle,
	ULONG ThreadInformationClass,
	PVOID ThreadInformation,
	ULONG ThreadInformationLength,
	PULONG ReturnLength);

typedef struct _THREAD_BASIC_INFORMATION {
	NTSTATUS ExitStatus;
	PVOID TebBaseAddress;
	CLIENT_ID ClientId;
	ULONG_PTR AffinityMask;
	LONG Priority;
	LONG BasePriority;
} THREAD_BASIC_INFORMATION;

// 启动中央监控（启动后台线程）。返回0成功
MixinRunTime_API int CSM_Start(void);

// 停止并清理（等待后台线程退出）
MixinRunTime_API void CSM_Stop(void);

// 手动注册线程（当前进程内或跨进程）
// pid==0 表示当前进程；tid 必须非0；thresholdBytes 单位字节
// 返回 0 成功，非0失败
MixinRunTime_API int CSM_RegisterThread(DWORD pid, DWORD tid, size_t thresholdBytes);

// 注销（按 tid）
// 返回 0 成功，非0未找到
MixinRunTime_API int CSM_UnregisterThread(DWORD tid);

// 设置自定义溢出回调（NULL 恢复默认）
MixinRunTime_API void CSM_SetOverflowHandler(CSM_OverflowHandler handler);

// 自动注册控制：enable(0/1), defaultThresholdBytes, enumIntervalMs（>=100ms）
// 自动注册只在本进程内枚举并注册新线程
MixinRunTime_API void CSM_EnableAutoRegister(int enable, size_t defaultThresholdBytes, DWORD enumIntervalMs);

// 配置轮询间隔（ms），建议 50~500 范围
MixinRunTime_API void CSM_SetPollIntervalMs(DWORD pollMs);

