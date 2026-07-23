#pragma once
#include "Include.h"
#include "Boolean.h"

#ifdef this
#define this self
#undef this
#endif
#ifdef __cplusplus
extern "C" {
#endif
#define TYPE_ANIMAL 0xA001
typedef struct VirtualFunction_Animal {
	unsigned int type_id;//类型id，标识对象所属类型

    void (*speak)(void* this);
    void (*destructor)(void* this);
} VirtualFunction_Animal;

MixinRunTime_API void Animal_Ctor(void* object_ptr);

MixinRunTime_API void Animal_Eat(void* this, const char* food);

#ifdef __cplusplus
}
#endif