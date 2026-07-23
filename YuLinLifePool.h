#pragma once

#include "Include.h"
#include "Boolean.h"

// ==================== 常量与限制（按需调高，但别乱） ====================
#define YLP_MAGIC      "YLLIFE\0\1" // 8 bytes: 标识(7) + 版本(1)
#define YLP_HEADER_SZ  20           // 固定头大小
#define YLP_ENDIAN_LE  0x01

// 上限（强制边界，防炸）
#define YLP_MAX_METHODS     1000000U
#define YLP_MAX_INSTANCES   1000000U
#define YLP_MAX_NAME        1024U
#define YLP_MAX_SIG         4096U
#define YLP_MAX_ASM         2048U
#define YLP_MAX_FILE_BYTES  (256U * 1024U * 1024U)

// Flags
#define YLP_FLAG_HEX_SIDECAR 0x1    // 旁路 .hex（调试可开启）

// Record Kind（内部区分流段）
#define YLP_SECTION_METHODS  0xA1
#define YLP_SECTION_INST     0xA2

// 句柄
typedef void* LP_HANDLE;

// ----- internal definitions -----
typedef struct {
    FILE* f;
    int writing;
    uint32_t methodCount;
    uint32_t instanceCount;
    uint32_t writtenMethods;
    uint32_t writtenInstances;
    long methodsOffset;    // where methods start (after header)
    long instancesOffset;  // after methods section (if needed)
} LP_CTX;

// ---- MetaRegistry + MetaInvoker (in-memory) ----

typedef struct {
    uint32_t hash;
    char* typeName;
    char* assembly;
} MetaType;


typedef struct {
    uint32_t hash;
    char* declType;
    char* name;
    char* sig;
} MetaMethod;

typedef struct {
    MetaMethod* methods;
    uint32_t methodCount;
    MetaType* types;
    uint32_t typeCount;
    // indexing
    uint32_t tableSize;
    uint32_t* methodIndexByHash; // size tableSize, store index+1 or 0
} MetaRegistry;

// Simple invoker mapping
typedef void (*MetaCallPtr)(void* instance, void** args, uint32_t argCount);
typedef struct {
    uint32_t key;
    MetaCallPtr ptr;
} InvEntry;

typedef struct {
    InvEntry* table;
    uint32_t size;
    uint32_t count;
} MetaInvoker;


// ==================== 写入侧 API ====================

    // 打开写入器（创建/覆盖）
    // flags: bit0=生成同名 .hex 调试旁路
MixinRunTime_API LP_HANDLE LP_OpenWriterW(const wchar_t* path, DWORD flags);

// 写一条方法记录：指纹哈希 + 声明类型 + 方法名 + 签名（UTF-8）
// 所有 UTF-8 参数可为 NULL + len=0
MixinRunTime_API Boolean LP_WriteMethod(LP_HANDLE h, UINT32 fingerprintHash, const char* declType, UINT16 declLen, const char* methodName, UINT16 nameLen, const char* signature, UINT16 sigLen);

// 写一条实例类型记录：类型哈希 + 类型全名 + 程序集名（UTF-8）
MixinRunTime_API Boolean LP_WriteInstance(LP_HANDLE h, UINT32 typeHash, const char* typeName, UINT16 typeLen, const char* assembly, UINT16 asmLen);

// 关闭并回填头信息 + CRC（严格校验计数）
MixinRunTime_API Boolean LP_CloseWriter(LP_HANDLE h, UINT32 methodCountExpected, UINT32 instanceCountExpected);

// 工具：FNV-1a 32
MixinRunTime_API UINT32 LP_Fnv1a32(const char* bytes, UINT32 len);

// ==================== 读取侧 API（顺序迭代） ====================

// 打开读取器
MixinRunTime_API LP_HANDLE LP_OpenReaderW(const wchar_t* path);

// 读取统计（来自头部）
MixinRunTime_API Boolean LP_QueryCounts(LP_HANDLE h, UINT32* outMethodCount, UINT32* outInstanceCount);

// 依次读取下一条方法记录；返回 FALSE 表示到末尾或出错
// 传入缓冲区用于承接 UTF-8 文本；不足则失败（返回 FALSE）
MixinRunTime_API Boolean LP_NextMethod(LP_HANDLE h, UINT32* outFingerprintHash, char* declBuf, UINT16 declCap, UINT16* outDeclLen, char* nameBuf, UINT16 nameCap, UINT16* outNameLen, char* sigBuf, UINT16 sigCap, UINT16* outSigLen);

// 依次读取下一条实例记录
MixinRunTime_API Boolean LP_NextInstance(LP_HANDLE h, UINT32* outTypeHash, char* typeBuf, UINT16 typeCap, UINT16* outTypeLen, char* asmBuf, UINT16 asmCap, UINT16* outAsmLen);

// 关闭读取器
MixinRunTime_API void LP_CloseReader(LP_HANDLE h);



MixinRunTime_API Boolean LP_WriteMethods(void* h, UINT32 fingerprintHash, const char* declType, UINT16 declLen, const char* methodName, UINT16 nameLen, const char* signature, UINT16 sigLen);

MixinRunTime_API Boolean LP_WriteInstances(void* h, UINT32 typeHash, const char* typeName, UINT16 typeLen, const char* assembly, UINT16 asmLen);

MixinRunTime_API Boolean LP_CloseWriters(void* h, UINT32 methodCountExpected, UINT32 instanceCountExpected);

// FNV-1a 32
MixinRunTime_API UINT32 LP_Fnv1a32s(const char* bytes, UINT32 len);

MixinRunTime_API void* LP_OpenReaderWs(const wchar_t* path);

MixinRunTime_API Boolean LP_QueryCountss(void* h, UINT32* outMethodCount, UINT32* outInstanceCount);

MixinRunTime_API Boolean LP_NextMethods(void* h, UINT32* outFingerprintHash, char* declBuf, UINT16 declCap, UINT16* outDeclLen, char* nameBuf, UINT16 nameCap, UINT16* outNameLen, char* sigBuf, UINT16 sigCap, UINT16* outSigLen);

MixinRunTime_API Boolean LP_NextInstances(void* h, UINT32* outTypeHash, char* typeBuf, UINT16 typeCap, UINT16* outTypeLen, char* asmBuf, UINT16 asmCap, UINT16* outAsmLen);

MixinRunTime_API void LP_CloseReaders(void* h);

MixinRunTime_API MetaRegistry* MetaRegistry_Creates(void);

MixinRunTime_API void MetaRegistry_Remove(MetaRegistry* r);

// MetaRegistry_LoadFromFiles 函数
MixinRunTime_API Boolean MetaRegistry_LoadFromFiles(MetaRegistry* r, const wchar_t* path);

MixinRunTime_API MetaMethod* MetaRegistry_FindMethodByHashs(MetaRegistry* r, uint32_t hash);

// Invoker
MixinRunTime_API MetaInvoker* MetaInvoker_Creates(uint32_t initialSize);

MixinRunTime_API void MetaInvoker_Remove(MetaInvoker* inv);


MixinRunTime_API Boolean MetaInvoker_Registers(MetaInvoker* inv, uint32_t hash, MetaCallPtr ptr);


MixinRunTime_API MetaCallPtr MetaInvoker_Gets(MetaInvoker* inv, uint32_t hash);

MixinRunTime_API int MetaInvoker_Invokes(MetaInvoker* inv, uint32_t hash, void* instance, void** args, uint32_t argCount);