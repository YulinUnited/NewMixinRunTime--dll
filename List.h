#pragma once
#include "MixinGarbageCollection.h"
#include "Util.h"
#include "Include.h"
#include "Object.h"
#include "Entity.h"



typedef struct {
	int* data;
	int size;
	int capacity;

	unsigned char element_is_ref;
}List_int;

typedef enum {
	VALUE,
	ENTITY,
	OBJECT
}ElementMode;

typedef struct {
	void** data;
	size_t size;
	size_t capacity;
	ElementMode mode;
}List;

typedef struct {
	Object** ObjectData;
	size_t ObjectSize;
	size_t ObjectCapacity;
}List_Object;

typedef struct {
	Entity** EntityData;
	size_t EntitySize;
	size_t EntityCapacity;
}List_Entity;

static inline void List_int_reserve(List_int* list, int new_capacity)
{
	if (new_capacity <= list->capacity)return;
	int new_cap = list->capacity == 0 ? 4 : list->capacity;

	while (new_cap < new_capacity)
	{
		new_cap *= 2;
	}

	int* new_data = (int*)MixinGC_Allocate(sizeof(int) * new_cap);

	if (list->data)
	{
		memcpy(new_data, list->data, sizeof(int) * list->size);
	}

	list->data = new_data;
	list->capacity = new_cap;
}

static inline void List_int_init(List_int* list)
{
	list->data = null;
	list->size = 0;
	list->capacity = 0;
	list->element_is_ref = 0;
}

static inline void List_int_add(List_int* list, int value)
{
	if (list->size >= list->capacity)
	{
		List_int_reserve(list, list->size + 1);
	}
	list->data[list->size++] = value;
}

static inline int List_int_get(List_int* list, int index)
{
	return list->data[index];
}

static inline void List_int_set(List_int* list, int index, int value)
{
	list->data[index] = value;
}

static inline void List_Object_Init(List_Object* list);
static inline void List_Object_Add(List_Object* list, Object* obj);
static inline Object* List_Object_Get(List_Object* list, size_t index);
static inline void List_Object_Remove(List_Object* list, size_t index);
static inline void List_Object_Clear(List_Object* list);

static inline void List_Entity_Init(List_Entity* list);
static inline void List_Entity_Add(List_Entity* list, Entity* entity);
static inline Entity* List_Entity_Get(List_Entity* list, size_t index);
static inline void List_Entity_Remove(List_Entity* list, size_t index);
static inline void List_Entity_Clear(List_Entity* list);

static void List_int_gc_scan(List_int* list, void(*mark)(void*));

