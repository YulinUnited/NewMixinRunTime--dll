#pragma once
#include "Include.h"
#include "Object.h"
#include "Entity.h"




typedef enum {
	ENTITY_METHOD,
	ENTITY_STATIC_METHOD,
	ENTITY_STATIC_BASE_METHOD,
	ENTITY_BASE_METHOD,
	OBJECT_METHOD,
	OBJECT_STATIC_METHOD,
	OBJECT_STATIC_BASE_METHOD,
	OBJECT_BASE_METHOD
}MethodType;

typedef struct {
	size_t size;//自身大小
	
	void* ptr;//自身数据
	void** paw;//指向自己数据的指针
	void* vptr;//虚函数指针
	void* List;//列表指针

	MethodType methodtype;//指向方法类型的指针

	Object* object;//指向对象的指针
	Entity* entity;//指向实体的指针

	const char* MethodName;//方法名称

	void(*invoke)(struct Method* method, void* this, void** args);
}Method;

typedef void(*MethodFunc)(void* this, void** args);

void Method_Dispatch(Method* method, void* this, void** args);
void Method_Remove(Method* method);

