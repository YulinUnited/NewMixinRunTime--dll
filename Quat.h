#pragma once
#include "Vector3.h"
#include "Include.h"

typedef struct { double x, y, z, w; } Quat;

MixinRunTime_API Quat Quat_Identity();
MixinRunTime_API Quat Quat_FromAxisAngle(Vector3 axis, double angle);
MixinRunTime_API Quat Quat_Multiply(Quat a, Quat b);
MixinRunTime_API Vector3 Quat_RotateVec3(Quat q, Vector3 v);
MixinRunTime_API Quat Quat_Normalize(Quat q);
MixinRunTime_API Quat Quat_Inverse(Quat q);
MixinRunTime_API Quat Quat_Slerp(Quat a, Quat b, double t);
