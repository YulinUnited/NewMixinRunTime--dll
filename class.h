#pragma once
#include "Include.h"
#include "Boolean.h"
#include "Method.h"

//#define class //暂不启用宏覆盖，根据需要决定是否要启用

typedef enum {
	OBJECT_STATIC_CLASS,
	OBJECT_DYNAMIC_CLASS,
	OBJECT_BASE_CLASS,
	ENTITY_BASE_CLASS,
	ENTITY_STATIC_CLASS,
	ENTITY_DYNAMIC_CLASS
}ClassType;


typedef struct {
	size_t class_size;//类大小，总计算
	size_t class_List_size;//类列表大小，内部列表大小

	Method** methods;//方法
	size_t method_count;
	size_t method_capacity;

	MethodType methodtype;//方法类型

	void* class_data;//类自身数据
#ifdef DEBUG
	void** class_data_ptr;//指向类自身数据的指针，当程序出错时，可以用于排查，可选
#endif
	char* class_name;//类名称
}Class;

MixinRunTime_API Class* Class_Create(const char* name, ClassType types);
MixinRunTime_API void Class_AddMethod(Class* cls, Method* method);
MixinRunTime_API Method* Class_FindMethod(Class* cls, const char* name);
MixinRunTime_API void Class_Invoke(Class* cls, const char* name, void* this, void** args);
MixinRunTime_API void Class_Remove(Class* cls);