#pragma once
#include "MixinGarbageCollection.h"
#include "Include.h"

MixinRunTime_API void* Mixin_StrDup(const char* src);
MixinRunTime_API void Mixin_StrFree(void* str);
MixinRunTime_API size_t Mixin_StrLen(const char* str);
MixinRunTime_API int Mixin_StrCmp(const char* a, const char* b);

