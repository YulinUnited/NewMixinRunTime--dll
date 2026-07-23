#pragma once
#include "Util.h"
#include "Include.h"
#include "Entity.h"
#include "Object.h"
#include "MixinGarbageCollection.h"

typedef struct {
	Entity* entity_list;
	Object* object_list;
}MethodList;

MixinRunTime_API void MethodList_Add(MethodList* methodlist);
MixinRunTime_API int MethodList_Clear(MethodList* methodlist);
MixinRunTime_API void MethodList_Remove(MethodList* methodlist);