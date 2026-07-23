#pragma once
/*为了消除跨平台兼容性，对此提供一些跨平台的属性与函数，目的是为了消除不同平台之间的对齐问题*/
/*为了准确区分不同跨平台的兼容性，如果需要跨平台会使用#if defined区分，不需要的则是直接写死*/

//
//有一些定义体并不是非要跨平台，带有注释的如8,8这种有大小偏移量的注释都是不需要考虑不同平台差异，因为都是固定的
//

#include "Include.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LongArray_Integer 80
	//无符号
	typedef struct {
		unsigned char Integer[LongArray_Integer];//80
	}NuInteger_Array_t;//80,2，8的倍数，即8 * 10 = 80；
	//有符号
	typedef struct {
		signed char Integer[LongArray_Integer];//80
	}NInteger_Array_t;//80,2

	typedef long long longlong;//8,8
	typedef unsigned long long ulonglong;//8,8
	typedef signed long long nlonglong;//8,8
#define MaxLongLong
	typedef longlong* P_Long_Long;//8,8
	typedef ulonglong* P_Ulong_Ulong;//8,8

	typedef longlong usn;//8,8
	typedef void* P_VOID;//8,8 or 4,4
	typedef unsigned long long pointer_64_int;//8,8

	typedef signed char Int8, * P_Int8;//1,1
	typedef signed short Int16, * P_Int16;//2,2
	typedef signed int Int32, * P_Int32;//4,4
	typedef signed long long Int64, * P_Int64;//8,8

	typedef unsigned char UInt8, * P_UInt8;//1,1
	typedef unsigned short UInt16, * P_UInt16;//2,2
	typedef unsigned int UInt32, * P_UInt32;//4,4
	typedef unsigned long long UInt64, * P_UInt64;//8,8

	typedef signed int Long32, * P_Long32;//4,4
	typedef unsigned int ULong32, * P_ULong32;//4,4
	typedef unsigned int Dword32, * P_Dword32;//4,4


	typedef unsigned long long System_W64;//C99后long long 统一为8,8字节
	typedef unsigned int System_W32;//C99后，int或者说int无论是哪一个C版本都是4字节
	typedef long long Int_Ptr, * P_Int_Ptr;//8,8
	typedef unsigned long long UInt_Ptr, * P_UInt_Ptr;//8,8

	typedef long long Long_Ptr, * P_Long_Ptr;//8,8
	typedef unsigned long long ULong_Ptr, * P_ULong_Ptr;//8,8
	//如果没有定义__int_32/64_t时，避免与关键字或标准库冲突
#ifndef __int_32_t
#define __int_32_t  int
#endif
#ifndef __int_64_t
#define __int_64_t  long long
#endif
	typedef __int_32_t INT_32_Ptr, * P_INT_32_Ptr;//4,4
	typedef unsigned __int_32_t UInt_32_Ptr, * P_UInt_32_Ptr;//4,4
	typedef __int_64_t Int_64_Ptr, * P_Int_64_Ptr;//8,8
	typedef unsigned __int_64_t UInt_64_Ptr, * P_UInt_64_Ptr;//8,8

#ifndef __int32_t
	typedef signed int __int32_t;//4,4字节是固定的，不需要区分不同平台
#endif
#ifndef __int64_t
#if defined(_WIN64)//如果是win64系统，否则一概按照long = 8,8字节处理
	typedef signed long long __int64_t;//8,8
#else 
	typedef signed long __int64_t;//如果不是win64，则是long，long在其他系统之下是8,8字节
#endif
#endif

#ifdef __cplusplus
}
#endif



/*对付其他非操作系统，例如Android、HarmonyOS等*/

#ifdef __cplusplus
extern "C" {
#endif



#ifndef PE_nint32
	typedef signed int PE_nint32;//无需多言，固定的神,4,4
#endif



#ifndef PE_nint64
#if defined(__ANDROID__)
	typedef signed long long PE_nint64;//8,8
#elif defined(__OHOS__)||defined(__LINUX__)&&!defined(__linux__)
	typedef signed long PE_nint64;//4,4(对windows x64来说是这样的)
#else
	typedef signed long long PE_nint64;//8,8
#endif
#endif



#ifndef PE_uint32
	typedef unsigned int PE_uint32;//4,4
#endif



#ifndef PE_uint64
#if defined(__ANDROID__)
	typedef unsigned long long PE_uint64;//8,8
#elif defined(__OHOS__)||defined(__LINUX__)&&!defined(__linux__)
	typedef unsigned long PE_uint64;//4,4(对windows x64来说是这样的)
#else 
	typedef unsigned long long PE_uint64;//8,8
#endif
#endif


	typedef long long PE_longlong;//8,8
	typedef signed long long PE_NLonglong;//8,8
	typedef unsigned long long PE_ULonglong;//8,8



#ifndef PE_Int64
#if defined(__ANDROID__)
	typedef long long PE_Int64;//8,8
#elif defined(__OHOS__)||defined(__LINUX__)||defined(__linux__)
	typedef long PE_Int64;//4,4(对windows x64来说是这样的)
#else
	typedef long long PE_Int64;//8,8
#endif
#endif



#ifndef PE_Int32
	typedef int PE_Int32;//4,4
#endif



#ifndef PE_LongDouble
	typedef long double PE_LongDouble;//不需要改变，因为8,8字节
#endif



#ifndef PE_nint32
	typedef signed int PE_nint32;//4,4
#endif


#ifndef PE_nint64_t
	typedef signed long PE_nint64_t;//4,4（对windows x64来说是这样的）
#endif


#ifndef PE_nuint32
	typedef unsigned long PE_nuint32;//4,4（对windows x64来说是这样的）
#endif


#ifndef PE_nuint64
	typedef unsigned long long PE_nuint64;//8,8
#endif

	typedef PE_nint32 PE_IntPtr32;//4,4
	typedef PE_nint64 PE_IntPtr64;//8,8

	typedef PE_nuint32 PE_UIntPtr32;//4,4
	typedef PE_nuint64 PE_UIntPtr64;//8,8

	MixinRunTime_API PE_nint32 getPE_IntPtr32(PE_nint32 ptr);
	MixinRunTime_API PE_nint64 getPE_IntPtr64(PE_nint64 ptr);

	MixinRunTime_API PE_nuint32 getPE_UIntPtr32(PE_nuint32 ptr);
	MixinRunTime_API PE_nuint64 getPE_UIntPtr64(PE_nuint64 ptr);

#define PE_NUINT_BYTES 72//8 * 9 = 72

	typedef struct {
		unsigned char array[PE_NUINT_BYTES];
	}PE_BigArray;//72,1

#ifndef PE_Size
	typedef unsigned long long PE_Size;//8,8
#endif
	typedef struct {
		long double manliage;//8,8
		PE_BigArray array;//72,1
		int shortarray;//4,4，四字节
		int shortarrays;//4,4，补充四字节凑齐八字节
	}PE_BigFloat;//88,8 = 8 + 72 = 80 + 4 + 4 = 88字节大小

	typedef struct {
		PE_nint64* limbs;//8,8
		PE_Size size;//8,8
		int sign;//4,4，四字节
		int shortarray;//4,4，补充四字节凑齐八字节
	}BigInt;//24,8 = 8 + 8 = 16 + 4 + 4 = 24字节大小

	typedef unsigned long long PE_E64;//仿W64,8,8
	typedef unsigned int PE_E32;//仿W32,4,4

	typedef long long PE_LongLong;//8,8
	typedef unsigned long long PE_ULongLong;//8,8
	typedef signed long long PE_NLongLong;//8,8

#ifdef __cplusplus
}
#endif