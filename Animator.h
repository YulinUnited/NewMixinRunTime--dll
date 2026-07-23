#pragma once
#include "Include.h"
#include "Mathf.h"
#include "Vector3.h"
#include "Boolean.h"
/*动画，可选*/

#ifdef __cplusplus
extern "C" {
#endif

    // ----- 基本类型 -----
    typedef struct {
        double time;
        double value;
    } Keyframe1D;//8,8

    typedef struct {
        double time;
        Vector3 value;
    } KeyframeVec3;//8 + 24 = 30,编译器自行补充2字节构成大小32，偏移量8

    typedef struct {
        double time;
        Quaternion value;
    } KeyframeQuat;//8 + 32 = 40,8

    typedef struct {
        const char* name;   // 注意：name 是否由 Animator 分配由调用者与 ownsClip 配合决定
        Keyframe1D* keys;
        int keyCount;
    } AnimationClip1D;//8 + 16 = 20 + 4 = 24,8

    typedef struct {
        const char* name;//8,8
        KeyframeVec3* keys;//32,8
        int keyCount;//4,4
    } AnimationClipVec3;//8 + 32 = 40 + 4 = 44,8,嗯...编译器告送我是24字节大小，有点意思

    typedef struct {
        const char* name;//8,8
        KeyframeQuat* keys;//32,8
        int keyCount;//4,4
    } AnimationClipQuat;//8 + 40 = 48 + 4 = 52,8,嗯...编译器告送我是24字节大小，有点不正常

    typedef enum {
        ANIM_TYPE_NONE = 0,
        ANIM_TYPE_1D,
        ANIM_TYPE_VEC3,
        ANIM_TYPE_QUAT
    } AnimationType;//4,4

    // AnimatorState - 结构体尽量保持平凡 POD（方便跨DLL使用）
    typedef struct {
        double currentTime;

        void* currentClip;      // pointer to one of AnimationClip{1D,Vec3,Quat}
        void* nextClip;

        AnimationType currentType; // current clip type
        AnimationType nextType;    // next clip type

        Boolean currentOwnsClip;  // 是否拥有 currentClip（为 true 时，可能会在 Remove 时 free）
        Boolean nextOwnsClip;     // 是否拥有 nextClip

        double transitionStart;
        double transitionDuration;
    } AnimatorState;//8 + 8 = 16 + 8 = 24 + 4 = 28 + 4 = 32 + 1 = 33 + 1 = 34 + 8 = 42 + 8 = 50,8,编译器自动补充6字节构成56,8的大小与偏移量

    // ----- 创建 / 销毁 -----
    MixinRunTime_API AnimatorState* AnimatorCreate1D(AnimationClip1D* clip);
    MixinRunTime_API AnimatorState* AnimatorCreateVec3(AnimationClipVec3* clip);
    MixinRunTime_API AnimatorState* AnimatorCreateQuat(AnimationClipQuat* clip);

    // 释放 AnimatorState。本函数默认只释放 AnimatorState 本体（不 free clip）
    MixinRunTime_API void Animator_removeAnimator(AnimatorState* state);

    // 强制删除：如果全局允许并且 state 标记 ownsClip，会同时释放 clip（keys + clip 本体）
    // 使用前请确保 clip/keys 是通过 malloc 分配的，且没有其他代码会再次访问它们。
    MixinRunTime_API void Animator_removeAnimator_Strict(AnimatorState* state);

    // ----- 播放控制 -----
    MixinRunTime_API void AnimatorUpdate(AnimatorState* state, double time);

    // 强类型播放接口（推荐使用，避免类型混用）
    // transitionDuration in same time units as 'time' (double)
    MixinRunTime_API void AnimatorPlay1D(AnimatorState* state, AnimationClip1D* clip, double transitionDuration);
    MixinRunTime_API void AnimatorPlayVec3(AnimatorState* state, AnimationClipVec3* clip, double transitionDuration);
    MixinRunTime_API void AnimatorPlayQuat(AnimatorState* state, AnimationClipQuat* clip, double transitionDuration);

    // 兼容型（仅当 state->currentType 已知时可用；若 state->currentType == ANIM_TYPE_NONE 则不允许）
    MixinRunTime_API void AnimatorPlay(AnimatorState* state, void* clip, double transitionDuration);

    // ----- 评估接口 -----
    MixinRunTime_API double AnimatorEvaluate1D(AnimatorState* state);
    MixinRunTime_API Vector3 AnimatorEvaluateVec3(AnimatorState* state);
    MixinRunTime_API Quaternion AnimatorEvaluateQuat(AnimatorState* state);

    // ----- 全局与本地释放控制 -----
    // 全局允许释放：返回先前的值（old）
    MixinRunTime_API Boolean Animator_EnableGlobalClipMixinGC_Free(Boolean enable);
    MixinRunTime_API Boolean Animator_GetGlobalClipMixinGC_Free(void);

    // 标记某个 state 的当前/下一个 clip 是否由 Animator 拥有（默认为 false）
    // 如果为 true，则在全局允许释放的前提下, RemoveAnimator_Strict 会释放 clip
    MixinRunTime_API void Animator_SetCurrentClipOwned(AnimatorState* state, Boolean owned);
    MixinRunTime_API void Animator_SetNextClipOwned(AnimatorState* state, Boolean owned);

    // ----- Clip 工厂（可选，方便分配/初始化 clip） -----
    // 如果你不需要工厂可以忽略这部分；如果使用这些函数，记得当你使用 Animator 管理 clip 时将 owned 标记设为 true。
    MixinRunTime_API AnimationClip1D* Animator_CreateClip1D(const char* name, int keyCount);
    MixinRunTime_API void Animator_removeClip1D(AnimationClip1D* clip);

    MixinRunTime_API AnimationClipVec3* Animator_CreateClipVec3(const char* name, int keyCount);
    MixinRunTime_API void Animator_removeClipVec3(AnimationClipVec3* clip);

    MixinRunTime_API AnimationClipQuat* Animator_CreateClipQuat(const char* name, int keyCount);
    MixinRunTime_API void Animator_removeClipQuat(AnimationClipQuat* clip);

#ifdef __cplusplus
}
#endif


