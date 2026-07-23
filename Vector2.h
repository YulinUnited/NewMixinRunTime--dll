#pragma once

#include "Mathf.h"
#include "Include.h"

MixinRunTime_API Vector2 Vector2_Add(Vector2 a, Vector2 b);
MixinRunTime_API Vector2 Vector2_Sub(Vector2 a, Vector2 b);
MixinRunTime_API Vector2 Vector2_Scale(Vector2 v, double s);
MixinRunTime_API double Vector2_Dot(Vector2 a, Vector2 b);
MixinRunTime_API double Vector2_Length(Vector2 v);
MixinRunTime_API Vector2 Vector2_Normalize(Vector2 v);
MixinRunTime_API Vector2 Vector2_Zero();

