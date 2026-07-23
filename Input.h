#pragma once
#include "Include.h"
#include "Boolean.h"
#include "InputEvent.h"
#include "KeyCode.h"
/*输入，可选*/

MixinRunTime_API void BindInputEvent(InputEvent* event);
//每一时刻
MixinRunTime_API void UpdateInputState(void);
//如果此运行时被用于Unity或类似的引擎时，可以提供部分兼容性，当然，只是一小部分
MixinRunTime_API int GetKey(KeyCode key);
MixinRunTime_API int GetKeyDown(KeyCode key);
MixinRunTime_API int GetKeyUp(KeyCode key);
//鼠标
MixinRunTime_API void GetMousePosition(int* x, int* y);