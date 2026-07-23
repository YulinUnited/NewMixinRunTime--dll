#pragma once

#include "Include.h"
#include "Boolean.h"


typedef void* NBT_HANDLE;

typedef enum {
    NBT_BYTE = 1,
    NBT_INT = 3,
    NBT_FLOAT = 5,
    NBT_STRING = 8,
    NBT_LIST = 9,
    NBT_COMPOUND = 10
} NBT_TYPE;

/* ================= 写入侧 API ================= */

// 打开写入器（创建/覆盖）flags 预留
MixinRunTime_API NBT_HANDLE NBT_OpenWriterW(const wchar_t* path, uint32_t flags);

// 写入原子标签（UTF-8 名称；字符串值同为 UTF-8）
MixinRunTime_API Boolean NBT_WriteByte(NBT_HANDLE h, const char* name, uint8_t  value);
MixinRunTime_API Boolean NBT_WriteInt(NBT_HANDLE h, const char* name, int32_t  value);
MixinRunTime_API Boolean NBT_WriteFloat(NBT_HANDLE h, const char* name, float    value);
MixinRunTime_API Boolean NBT_WriteString(NBT_HANDLE h, const char* name, const char* value);

// 写入容器（开始/结束）
MixinRunTime_API Boolean NBT_StartCompound(NBT_HANDLE h, const char* name);
MixinRunTime_API Boolean NBT_EndCompound(NBT_HANDLE h);

MixinRunTime_API Boolean NBT_StartList(NBT_HANDLE h, const char* name, NBT_TYPE elemType);
MixinRunTime_API Boolean NBT_EndList(NBT_HANDLE h);

// 关闭写入器（会回填根元素计数）
MixinRunTime_API Boolean NBT_CloseWriter(NBT_HANDLE h);


/* ================= 读取侧 API ================= */

// 打开读取器
MixinRunTime_API NBT_HANDLE NBT_OpenReaderW(const wchar_t* path);

// 顺序读取“下一个”标签头：返回 type + name
// 返回 False 表示已达当前容器末尾或读取失败
MixinRunTime_API Boolean NBT_Next(
    NBT_HANDLE h,
    NBT_TYPE* outType,
    char* nameBuf, uint16_t nameCap, uint16_t* outNameLen);

// 获取紧随其后的**原子**值（需在 NBT_Next 返回 BYTE/INT/FLOAT/STRING 后调用）
MixinRunTime_API uint8_t  NBT_GetByte(NBT_HANDLE h);
MixinRunTime_API int32_t  NBT_GetInt(NBT_HANDLE h);
MixinRunTime_API float    NBT_GetFloat(NBT_HANDLE h);

// 获取字符串值（内部返回指向临时缓冲区的指针；下次调用会覆盖）
// 如需安全，请自己复制
MixinRunTime_API const char* NBT_GetString(NBT_HANDLE h);

// 进入/退出容器（当前实现为兼容占位，无操作，始终返回 True）
MixinRunTime_API Boolean NBT_EnterCompound(NBT_HANDLE h);
MixinRunTime_API Boolean NBT_ExitCompound(NBT_HANDLE h);
MixinRunTime_API Boolean NBT_EnterList(NBT_HANDLE h);
MixinRunTime_API Boolean NBT_ExitList(NBT_HANDLE h);

// 关闭读取器
MixinRunTime_API void NBT_CloseReader(NBT_HANDLE h);

