#pragma once

#include"Include.h"
#include"Boolean.h"

typedef struct {
	size_t size;//自身大小
	size_t data_size;//数据大小
	int64_t entity_id;//实体ID

	void* data_ptr;//数据指针
	void* data;//给MixinGarbageCollection的数据源，记载对象本身的数据流程/MixinGC分配的原始地址
	void* Method_ptr;//方法指针
	void** MethodPtr_ptr;//方法指针的指针

	Boolean forceDead;//强制死亡，直接激活回收逻辑
	Boolean isEntity;//是否是一个实体对象
	Boolean isDead;//死亡标记，它不会立刻回收，允许你有一定的时间反悔或重新启用

	char* name;
}Entity;//72,8
//定义entity关键字，对标Entity*实际上没什么卵用，占位符，可能永远用不上
//在MixinCompiler中定义的entity是标识符，用来标记一个类为实体类，没有除了重载外所有的多态性
//这里的entity只是一个占位符
typedef Entity* entity;

MixinRunTime_API void setDeath();
MixinRunTime_API void setDead(Entity* entity);
MixinRunTime_API void* Create_Entity(size_t size, int64_t entity_id);
MixinRunTime_API void* Entity_Free(Entity* entity);
MixinRunTime_API void Entity_Free_Data();
MixinRunTime_API Entity* getEntityPtr();

