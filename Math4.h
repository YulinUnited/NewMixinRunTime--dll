#pragma once
#include "Vector3.h"
#include "Vector4.h"

typedef struct { double m[4][4]; }Math4;

MixinRunTime_API Math4 Math4_Translate(Vector3 v);
MixinRunTime_API Math4 Math4_Scale(Vector3 v);
MixinRunTime_API Math4 Math4_RotateX(double angleRad);
MixinRunTime_API Math4 Math4_RotateY(double angleRad);
MixinRunTime_API Math4 Math4_RotateZ(double angleRad);
MixinRunTime_API Math4 Math4_Multiply(Math4 a, Math4 b);
MixinRunTime_API Vector4 Math4_MultiplyVector4(Math4 m, Vector4 v);
MixinRunTime_API Math4 Math4_Identity(void);
MixinRunTime_API Math4 Math4_LookAt(Vector3 eye, Vector3 target, Vector3 up);
MixinRunTime_API Math4 Math4_Perspective(double fovY, double aspect, double nears, double fars);
MixinRunTime_API Math4 Math4_Ortho(double left, double right, double bottom, double top, double nears, double fars);

