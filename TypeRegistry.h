#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TypeInfo {
    const char* typeName;
    size_t size;
    struct TypeInfo* baseType;
} TypeInfo;

MixinRunTime_API TypeInfo* RegisterType(const char* typeName, size_t size);
MixinRunTime_API TypeInfo* FindType(const char* typeName);
MixinRunTime_API size_t GetTypeSize(TypeInfo* type);
MixinRunTime_API void TypeRegistry_Init(void);
MixinRunTime_API void TypeRegistry_Shutdown(void);

#ifdef __cplusplus
}
#endif