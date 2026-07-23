#pragma once

#include "Vector3.h"



MixinRunTime_API Vector4 Vector4_Add(Vector4 a, Vector4 b);
MixinRunTime_API Vector4 Vector4_Sub(Vector4 a, Vector4 b);
MixinRunTime_API Vector4 Vector4_Scale(Vector4 v, float s);
MixinRunTime_API float Vector4_Dot(Vector4 a, Vector4 b);
MixinRunTime_API float Vector4_Length(Vector4 v);
MixinRunTime_API Vector4 Vector4_Normalize(Vector4 v);

MixinRunTime_API Vector4 Vector4_Cross(Vector4 a, Vector4 b);
MixinRunTime_API Vector4 Vector4_FromVector3(Vector3 v, float w);
MixinRunTime_API Vector4 Vector4_FromAxisAngle(Vector3 axis, float angle);

