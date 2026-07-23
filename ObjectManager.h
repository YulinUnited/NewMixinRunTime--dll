#pragma once
#include "Include.h"
#include "Boolean.h"
#include "Object.h"

MixinRunTime_API Boolean isRetrieve();
MixinRunTime_API void setRetrieve(Boolean boolean);
MixinRunTime_API void registerType(const char* typeName, Destructor destructor);
MixinRunTime_API void* createObject(const char* typeName, size_t size);
MixinRunTime_API void incrementRefCount(void* ptr);
MixinRunTime_API void decrementRefCount(void* ptr);
MixinRunTime_API void removeObject(void* ptr);
MixinRunTime_API void removeAllObjects(void);
MixinRunTime_API size_t getObjectCount(void);
MixinRunTime_API void debugPrintAllObjects(void);
MixinRunTime_API int64_t getRefCount(void* ptr);