#pragma once

#include "Boolean.h"
#include "Include.h"
#define MATHF_PI 3.14159265358979323846
#define MATHF_PI_2 (MATHF_PI / 2.0)
#define MATHF_PI_4 (MATHF_PI / 4.0)
#define MATHF_TAU (2.0 * MATHF_PI)  // 2π
#define MATHF_DEG2RAD (MATHF_PI / 180.0)
#define MATHF_RAD2DEG (180.0 / MATHF_PI)
#define MATHF_E 2.71828182845904523536
#define MATHF_MPSILON 1e-6f
#define MATHF_INFINITY (1.0/0.0)

#define MATHF_EPSILON   1e-6f

#define MATHF_CLAMP01(value) ((value) < 0.0f ? 0.0f : (value) > 1.0f ? 1.0f : (value))
#define MATHF_CLAMP(value, min, max) ((value) < (min) ? (min) : (value) > (max) ? (max) : (value))
#define MATHF_LERP(a, b, t) ((a) + ((b) - (a)) * MATHF_CLAMP01(t))
#define MATHF_LERP_UNCLAMPED(a, b, t) ((a) + ((b) - (a)) * (t))

#define MATHF_LOGIC_INFINITE INFINITY
#define MATHF_LOGIC_MIN (-DBL_MAX)

#ifndef NAN
#ifdef  __cplusplus
#define NAN 0.0/0.0
#else
#define NAN 0.0 * MATHF_INFINITY
#endif
#endif

typedef struct {
	double x;
	double y;
} Vector2;

typedef struct {
	double x;
	double y;
	double z;
} Vector3;

typedef struct {
	double x;
	double y;
	double z;
	double w;
} Vector4;

typedef struct {
	double m[4][4];
} Matrix4x4;

typedef struct {
	double r;
	double g;
	double b;
	double a;
} Color;

typedef struct {
	double x;
	double y;
	double z;
	double w;
} Quaternion;

typedef struct {
	double x;
	double y;
} Point;

typedef struct {
	double width;
	double height;
} Size;

typedef struct {
	Point origin;
	Size size;
} Rect;

typedef struct {
	double x;
	double y;
	double width;
	double height;
} Bounds;

typedef struct {
	double x;
	double y;
	double z;
	double width;
	double height;
	double depth;
} Bounds3D;

typedef struct {
	double x;
	double y;
	double z;
	double w;
	double h;
	double d;
} Box;

typedef struct {
	double x;
	double y;
	double z;
} Euler;

typedef struct {
	double x;
	double y;
	double z;
} AxisAngle;

typedef struct {
	double real;
	double imag;
} Complex;

typedef struct {
	double real;
	double imag;
	double jmag;
	double kmag;
} QuaternionComplex;

typedef struct {
	double x;
	double y;
	double z;
	double w;
	double h;
	double d;
} HyperBox;

typedef struct {
	double x;
	double y;
	double z;
	double w;
	double h;
	double d;
	double e;
} HyperBox5D;
#pragma pack(push,1)
typedef struct {
	uint64_t mantissa;
	int32_t exponent;
	uint8_t sign;
}LogicDouble;
#pragma pack(pop)

// 数值函数实现：双精度（double）

MixinRunTime_API double Mathf_Clamp(double x, double min, double max);


MixinRunTime_API double Mathf_Log(double value);


MixinRunTime_API double Mathf_Sin(double angle);


MixinRunTime_API double Mathf_Cos(double angle);


MixinRunTime_API double Mathf_Tan(double angle);


MixinRunTime_API double Mathf_Asin(double value);


MixinRunTime_API double Mathf_Acos(double value);


MixinRunTime_API double Mathf_Atan(double value);


MixinRunTime_API double Mathf_Atan2(double y, double x);


MixinRunTime_API double Mathf_Sqrt(double value);

MixinRunTime_API double Mathf_Sqrtf(double value, double value1);


MixinRunTime_API double Mathf_Abs(double value);


MixinRunTime_API double Mathf_Min(double a, double b);


MixinRunTime_API double Mathf_Max(double a, double b);


MixinRunTime_API double Mathf_Lerp(double a, double b, double t);


MixinRunTime_API double Mathf_Clamp01(double value);

MixinRunTime_API double Mathf_Exp(double x);

MixinRunTime_API double Mathf_LerpUnclamped(double a, double b, double t);


// 数值函数实现：单精度（float）

MixinRunTime_API float Sqrt(float value);

MixinRunTime_API float Sqrtf(float value, float value1);


MixinRunTime_API float Sin(float angle);

//MixinRunTime_API float Sinf(float angle, float angle1);


MixinRunTime_API float Cos(float angle);

//MixinRunTime_API float Cosf(float angle, float angle1);


MixinRunTime_API float Abs(float value);

//MixinRunTime_API float Absf(float value, float value1);


MixinRunTime_API float Sign(float x);

//MixinRunTime_API float Signf(float x, float x1);

MixinRunTime_API float Lerp(float a, float b, float t);

//MixinRunTime_API float Lerpf(float a, float b, float t, float t1);

MixinRunTime_API float Clamps(float value);


MixinRunTime_API float LerpUnclamped(float a, float b, float t);


MixinRunTime_API float Min(float a, float b);

MixinRunTime_API float Max(float a, float b);

// 浮动版夹取函数
MixinRunTime_API float Clamp(float x, float min, float max);

MixinRunTime_API float Exp(float x);

//整数型
MixinRunTime_API long Mathf_Integer_Sqrt(long value);

MixinRunTime_API long Mathf_Integer_Sqrtf(long value, long value1);

MixinRunTime_API long Mathf_Integer_Sin(long angle);

MixinRunTime_API long Mathf_Integer_Cos(long angle);

MixinRunTime_API long Mathf_Integer_Abs(long value);

MixinRunTime_API long Mathf_Integer_Sign(long x);

MixinRunTime_API long Mathf_Integer_Lerp(long a, long b, long t);

MixinRunTime_API long Mathf_Integer_Clamps(long value);

MixinRunTime_API long Mathf_Integer_LerpUnclamped(long a, long b, long t);

MixinRunTime_API long Mathf_Integer_Min(long a, long b);

MixinRunTime_API long Mathf_Integer_Max(long a, long b);

MixinRunTime_API long Mathf_Integer_Clamp(long x, long min, long max);

MixinRunTime_API long Mathf_Integer_Exp(long x);

MixinRunTime_API long Mathf_Integer_Log(long value);

MixinRunTime_API double random();//未完成

