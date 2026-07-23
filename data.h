#pragma once
#include "Include.h"
#include "Boolean.h"
#include "MixinGarbageCollection.h"

/* ---------------------------
   Core runtime type system
   --------------------------- */

typedef uint32_t TypeId;

typedef struct TypeInfo {
    TypeId id;
    const char* name;
    size_t size;      // sizeof the type
    // future: alignment, serialize/deserialize hooks, copy/compare functions
} TypeInfo;

typedef struct TypeRegistry {
    TypeInfo** items;
    size_t count;
    size_t cap;
    TypeId next_id;
} TypeRegistry;

/* ---------------------------
   DataParameter / DataEntry
   --------------------------- */

typedef struct DataParameter {
    TypeInfo* types;
    char* name;
    uint64_t id; // opaque id for cross-language binding
} DataParameter;

typedef struct DataEntry {
    TypeInfo* types;   // what type this entry is supposed to hold
    void* data;       // allocated buffer of size type->size (or NULL)
    Boolean isDirty;
} DataEntry;


MixinRunTime_API void registry_ensure_capacity(size_t want);
MixinRunTime_API TypeInfo* RegisterType(const char* name, size_t size);
MixinRunTime_API TypeInfo* FindTypeByName(const char* name);
MixinRunTime_API void DumpRegisteredTypes(void);
MixinRunTime_API DataParameter* CreateDataParameter(TypeInfo* types, const char* name);
MixinRunTime_API void DestroyDataParameter(DataParameter* p);
MixinRunTime_API DataEntry* CreateDataEntry(DataParameter* param, const void* src);
MixinRunTime_API void DestroyDataEntry(DataEntry* e);
MixinRunTime_API void HandleTypeMismatch(DataEntry* entry, TypeInfo* expectedType, const void* src, size_t srcSize);
MixinRunTime_API Boolean SetData(DataEntry* entry, TypeInfo* types, const void* src, size_t srcSize);
MixinRunTime_API void* GetDataRaw(DataEntry* entry);
MixinRunTime_API void MarkClean(DataEntry* entry);
MixinRunTime_API void MarkDirty(DataEntry* entry);