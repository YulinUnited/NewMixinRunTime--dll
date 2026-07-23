#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_TYPE_NAME_LEN 64
#define MAX_TYPE_REGISTRY 128
#define INITIAL_CAPACITY 10 // 初始容量
#define MAX_OBJECTS 100

#include "Include.h"
#include "Boolean.h"
#include "VirtualFunction.h"

    //#include "runTime_types.h"

    /*C版Object，为了适配MixinGC*/
    typedef struct {
        size_t size; // 对象的大小（以字节为单位）
        size_t refCount;//引用计数，避免强制释放

        void* raw;//对象数据源，记载对象本身的数据流程/MixinGC分配的原始地址
        void* ptr;//对象指针，对标对象本身的数据源/对象实际数据地址
        //void** vptr;//虚函数指针
		const void* vptr;//虚函数指针，指向虚函数表

        Boolean isObject;//是否是对象体
        Boolean isRemove;//是否移除对象
        Boolean isAlive;//是否还活着

		unsigned int type_id;//类型id，标识对象所属类型
        int64_t object_id;//对象id

        char name[MAX_TYPE_NAME_LEN];//名称
        char payload;//对象字节

    } Object;//128,8

    //定义object关键字为Object*指针，占位用，实际上具体干什么未知
    typedef Object* object;//8,8(实际上应该是128,8)

    typedef struct {
        void** objectmethod;//指向对象方法的指针的指针
        void* objectmethodptr;//指向对象方法的指针
        char obhectmethodname;//对象方法名称
        char* objectmethodnameptr;//指向对象方法名称的指针
    }ObjectMethod;//32,8

    typedef struct {
        Object* objects;
        Object** move_object_ptr;
        size_t count;
        size_t capacity;
    }ObjectList;//32,8

    typedef struct {
        char typeName[MAX_TYPE_NAME_LEN];
    }Header;//64,1

    typedef void (*Destructor)(void*);

    typedef struct {
        char typeName[MAX_TYPE_NAME_LEN];
        Destructor destructor;
    } TypeEntry;//72,8

    static TypeEntry registry[MAX_TYPE_REGISTRY];

    static ObjectList manager = { NULL, 0, 0 };
    static int registryCount = 0;
    static long idCounter = 0;

    /*分配对象*/
    MixinRunTime_API Object* Object_Create(uint64_t object_id, Boolean isRemove, void* data, size_t data_size);
    /*将对象标记为弃用，它会被MixinGC自动清理，但是在清理前还会留在内存中*/
    MixinRunTime_API void Object_Destroy(Object* object);
    /*分配对象的指针，指向指针的指针*/
    MixinRunTime_API void Object_Malloc(Object** object);
    /*将对象真正回收，立刻回收*/
    MixinRunTime_API void Object_Free(Object* object);
    /*将对象标记为重新启用*/
    MixinRunTime_API void Object_Start(Object* object);
    /*获取对象指针*/
    MixinRunTime_API Object* getObjectPtr();

    /*不暴露函数*/
    static Object* getObjectFromPtr(void* ptr) {
        if (!ptr) return NULL;
        return (Object*)((char*)ptr - sizeof(Object));
    }

    static Header* getHeaderFromPtr(void* ptr) {
        if (!ptr) return NULL;
        return (Header*)((char*)ptr - sizeof(Object) - sizeof(Header));
    }

#ifdef __cplusplus
}
#endif