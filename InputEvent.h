#pragma once
#include "Boolean.h"
#include "Include.h"
/*输入事件，可选*/

typedef struct {
	Boolean isGlobalMark;
}InputEvent;

MixinRunTime_API Boolean getInputEvent();
MixinRunTime_API Boolean setInputEvent(Boolean boolean);
MixinRunTime_API Boolean InputEvent_Init(void);
MixinRunTime_API Boolean InputEvent_Remove(void);