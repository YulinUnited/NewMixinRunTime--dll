#pragma once


#include "Mathf.h"

MixinRunTime_API Vector3 Vector3_Add(Vector3 a, Vector3 b);
MixinRunTime_API Vector3 Vector3_Sub(Vector3 a, Vector3 b);
MixinRunTime_API Vector3 Vector3_Scale(Vector3 v, float s);
MixinRunTime_API double Vector3_Dot(Vector3 a, Vector3 b);
MixinRunTime_API Vector3 Vector3_Cross(Vector3 a, Vector3 b);
MixinRunTime_API double Vector3_Length(Vector3 v);
MixinRunTime_API Vector3 Vector3_Normalize(Vector3 v);

MixinRunTime_API Vector3 Vector3_Zero(void);


