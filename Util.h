#pragma once

/*
* NewMixinRunTime与MixinCompiler不可变更的绝对原则：
* 
* 1：整数值是整数值，例如IntSigned它只是整数值，带有Ptr只是因为getIntSigned要的是nint指针;
* 2：指针是指针，它是地址的直接获取来源也是呈现方式，没有指针是整数值，也不存在整数值就是指针的这种极其危险的说法;
* 3：禁止将地址作为整数值换算，也不准整数值与地址换算，我不管编程界如何理解，这一条钢铁规则适用于NewMixinRunTime与MixinCompiler;
* 4：使用Ai时，如果被新随我心意运行时或随我心意编译器检测出任何试图用整数值套指针的操作，运行时与编译器均可以无条件中断线程运行;
* 5：我允许开发者犯错，绝对不容许将整数值与指针混用的最低级最不可原谅的错误;
* 6：我允许Ai犯错，更不容许Ai犯下将指针与整数值兑换的行为，不管是为了所谓的“安全”还是什么借口的，编程从无安全可言，要安全那就杀死所有的编程行业;
* 
* 如果违反上述任何一条不容违反的规则，造成的一切后果由自己承担，此声明取消所谓的“Ai犯错与其开发公司无责任”的说法，法不责众，此原则对Ai与其创作公司统一生效;
*/

#include "Boolean.h"
#include "Include.h"

#define UINT616_BYTES 80//从77改为80，8的倍数
#define NINT_BYTE 33
#define NUINT128 16

#define UINT616_BITS 616
#define UINT616_MAX_INIT \
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
0x00,0x00,0x00
#define UINT616_MIN_INIT {0}
#ifndef null
#ifdef __cplusplus
#define null nullptr
#else
#define null ((void*)0)
#endif
#endif // !null
extern Boolean g_running;//运行时状态

extern Boolean g_runtime_dead;//运行时是否死亡

extern HANDLE g_hStopEvent;//线程事件

typedef enum {
    RUNTIME_NORMAL = 0,
    RUNTIME_MEMORY_PRESSURE,
    RUNTIME_EMERGENCY,
    RUNTIME_DEAD
}RunTimeState;//4,4

extern RunTimeState g_runtime_state;

#ifdef __cplusplus
extern "C" {
#endif

    //超级大数
    typedef struct {
        unsigned char exponent_data[UINT616_BYTES];
    }uint616_t;//80,1

    static const uint616_t UINT616_MAX = { {UINT616_MAX_INIT} };
    static const uint616_t UINT616_MIN = { {UINT616_MIN_INIT} };

    typedef long double _unArray_t;//8,8

    typedef uint616_t BigArray;//80,1
#ifdef byte
#undef byte
#endif
#ifdef Byte
#undef Byte
#endif
#define Byte unsigned char
#define byte signed char

    typedef signed char few;//1,1

    typedef signed long long nint64_t;//8,8

    typedef struct {
        unsigned char array[2];
    }ushort;//2,1

    typedef struct {
        signed char array[2];
    }Short;//没办法，short是关键字，C不存在重载这一说法

#ifdef type
#undef type
#endif
#define type void*

#if defined(_WIN64)||defined(__x86_64__)||defined(__aarch64__)
    typedef unsigned long long ulong;//8,8
#else
    typedef unsigned long ulong;//4,4
#endif

    typedef signed char sbyte;//1,1

    typedef unsigned int uint;//4,4

#if defined(_WIN64)||defined(__x86_64__)||defined(__aarch64__)
    typedef unsigned long long nuint_64_t;//8,8
#else
    typedef unsigned long nuint_32_t;//4,4
#endif

#if defined(_WIN64)||defined(__x86_64__)||defined(__aarch64__)
    typedef signed long long nint_64_t;//8,8
#else
    typedef signed long nint_32_t;//4,4
#endif

#if defined(_WIN64)||defined(__x86_64__)||defined(__aarch64__)
    typedef nuint_64_t nuint;//8,8
#else
    typedef nuint_32_t nuint;//4,4
#endif

#if defined(_WIN64)||defined(__x86_64__)||defined(__aarch64__)
    typedef nint_64_t nint;//8,8
#else
    typedef nint_32_t nint;//4,4
#endif

    typedef nint IntSigned;//8,8

    typedef nuint UIntSigned;//8,8

    MixinRunTime_API IntSigned getIntSigned(nint ptr);

    MixinRunTime_API UIntSigned getUIntSigned(nuint ptr);

    MixinRunTime_API void* get(type types);
    MixinRunTime_API void* getObject();

    MixinRunTime_API void* PointerChange(void* pointer);

    MixinRunTime_API Boolean getType(type types);

    typedef struct {
        long double mantissa;
        uint616_t exponent;
        int sign;//这里4字节
        int shortarray;//填补剩下4字节使其平齐为8字节
    }BigFloat;//96,8，编译器自动补充7字节对齐，8 + 80 = 88 + 4 = 92 + 4 = 96,对齐在这里是8大概率指的是对齐偏移量，即：0，4，8

    typedef struct {
        nint_64_t* limbs;//8
        size_t length;//8
        int sign;//4
        int shortarray;//4
    }BigInt;//24,8,补充齐剩下4字节，8 + 8 = 16 + 4 = 20 + 4 = 24字节,对齐在这里是8大概率指的是偏移量，即0，4，8

    //下面的是MixinCompiler的专属数组，在这里属于对齐
    typedef long float longFloat;//8,8

    typedef unsigned long int ulongInt;//4,4

    typedef unsigned int short UIntShort;//2,2

    typedef signed short int NShortInt;//2,2

    typedef short IntLeast_8_t;//2,2
    typedef signed long long nlong;//8,8,有符号长数


    //unintX_t与nuintX_t系列是为了避免与C标准库混淆,不属于MixinCompiler的内容

    /*unint等同于nuint泛式*/
    typedef struct {
        unsigned char array[2];
    }unint16_t;//2,1
    /*nuint等同于nint泛式*/
    typedef struct {
        signed char array[2];
    }nuint16_t;//2,1

    
    typedef signed int nint32_t;//4,4

    typedef unsigned int unint32_t;//4,4

    typedef signed long nuint64_t;//4,4

    typedef unsigned long unint64_t;//4,4

    typedef struct {
        signed char array[NUINT128];//8 + 8 = 16
    }nuint128_t;//16,1

    typedef struct {
        unsigned char array[NUINT128];//8 + 8 = 16
    }unint128_t;//16,1

    typedef enum {
        TYPE_BIGINT,
        TYPE_BIGFLOAT
    }NumberType;//4,4

    typedef struct {
        NumberType types;//4,4
        int shortarray;//因为全部计算的话是140字节，不是8的位数，在这里填充4字节凑齐144
        union {
            int64_t i64;//8,8
            double f64;//8,8
            BigInt* bigint;//24,8
            BigFloat* bigfloat;//96,8
        };
    }Number;//16,8，实际上应该是4 + 8 = 12 + 8 = 20 + 24 = 44 + 96 = 140字节大小

#ifdef __cplusplus
}
#endif
