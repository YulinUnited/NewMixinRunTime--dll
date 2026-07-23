#pragma once
/*半成品设计，不作为完整设计流程*/
#include "Include.h"
#include "Object.h"
#include "Entity.h"
#include "Util.h"

typedef struct {
	Object* object;
	Entity* entity;
}Getting;

MixinRunTime_API void* getUnknownPtr(void* payload);
MixinRunTime_API Object* getObjectType();
MixinRunTime_API void getNumber(Number* number);
MixinRunTime_API void* Malloc_Unknown_Class(size_t ptr);
MixinRunTime_API void Unknown_Class_Free(void* ptr);