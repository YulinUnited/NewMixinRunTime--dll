/*在使用Boolean.h前，请务必考虑好你的选择，冗沉但必要*/

#pragma once
#ifndef BOOLEAN_H
#define BOOLEAN_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
	typedef uint8_t Boolean;

	//在使用此型号前，请保证您使用的操作系统或编程语言没有对Boolean类型进行定义
	// 或对True重定义，以避免冲突
#define True ((Boolean)1)
	//在使用此型号前，请保证您使用的操作系统或编程语言没有对Boolean类型进行定义
	// 或对False重定义，以避免冲突
#define False ((Boolean)0)

#define Boolean_TO_INT(b) ((b) ? 1 : 0)
#define INT_TO_Boolean(i) ((i) ? True : False)

#define Boolean_Is_True(b)((b)==True)
#define Boolean_Is_False(b)((b)==False)




     // 安全的布尔操作
    static inline Boolean Boolean_And(Boolean a, Boolean b) {
        return (a && b) ? True : False;
    }

    static inline Boolean Boolean_Or(Boolean a, Boolean b) {
        return (a || b) ? True : False;
    }

    static inline Boolean Boolean_Not(Boolean a) {
        return (a == False) ? True : False;
    }

    static inline Boolean Boolean_Xor(Boolean a, Boolean b) {
        return (a != b) ? True : False;
    }

    // 数组操作
    static inline Boolean Boolean_All(const Boolean* array, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            if (array[i] == False) return False;
        }
        return True;
    }

    static inline Boolean Boolean_Any(const Boolean* array, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            if (array[i] == True) return True;
        }
        return False;
    }


#ifdef __cplusplus
}
#endif // __cplusplus
#endif // BOOLEAN_H