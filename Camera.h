#pragma once

#include "Include.h"
#include "Boolean.h"
#include "Mathf.h"
#include "Vector3.h"
/*相机，可选*/
// ----------------- 相机类型 -----------------
typedef enum {
    CAMERA_PERSPECTIVE = 0,
    CAMERA_ORTHOGRAPHIC = 1
} CameraType;//4,4

// ----------------- 相机状态结构 -----------------
typedef struct {
    Boolean isActive;//1,1
    Boolean isRemove;//1,1
    Boolean isDead;//1,1
    Boolean forceDead;//1,1

    CameraType types;//4,4

    Vector3 position;//24,8
    Vector3 target;//24,8
    Vector3 up;//24,8
    Vector3 right;//24,8
    Vector3 forward;//24,8

    // 透视投影参数
    double fovY;//8,8
    double aspect;//8,8
    double nearPlane;//8,8
    double farPlane;//8,8

    // 正交投影参数
    double orthoLeft;//8,8
    double orthoRight;//8,8
    double orthoBottom;//8,8
    double orthoTop;//8,8

    // 相机控制参数
    double moveSpeed;//8,8
    double rotationSpeed;//8,8
    double zoomSpeed;//8,8

    // 内部状态
    int dirty;//4,4
    double viewMatrix[16];//128,8
    double projMatrix[16];//128,8

    // 平滑跟随和旋转
    Vector3 targetPosition;//24,8
    Vector3 targetForward;//24,8
    Vector3 velocity;//24,8
    Vector3 angularVelocity;//24,8
    double smoothTime;//8,8
    double lastUpdateTime;//8,8
    Boolean useSmoothFollow;//1,1
    Boolean useSmoothRotation;//1,1

} CameraState;//(1 * 4 ) = 4 + 4 = 8 + (24 * 5) = 128 + ( 8 * 5 ) = 168 + (8 * 4) = 200 + (8 * 3) = 224 + 4 = 228 + (128 * 2) = 484 + (24 * 4) = 580 + (8 * 2) = 596 + 2 = 598大小，编译器补充2字节构成600字节大小，8偏移量

// ----------------- 生命周期 -----------------
MixinRunTime_API Boolean Camera_Initialize(CameraState* camera);
MixinRunTime_API Boolean Camera_Update(CameraState* camera, double deltaTime);
MixinRunTime_API void Camera_Cleanup(CameraState* camera);

// ----------------- 状态检查 -----------------
MixinRunTime_API Boolean Camera_IsActive(const CameraState* camera);
MixinRunTime_API Boolean Camera_ShouldRemove(const CameraState* camera);

// ----------------- 矩阵获取 -----------------
MixinRunTime_API void Camera_GetViewMatrix(CameraState* camera, double* viewMatrix);
MixinRunTime_API void Camera_GetProjectionMatrix(CameraState* camera, double* projMatrix);
MixinRunTime_API void Camera_GetViewProjectionMatrix(CameraState* camera, double* viewProjMatrix);

// ----------------- 相机控制 -----------------
MixinRunTime_API void Camera_SetPosition(CameraState* camera, Vector3 position);
MixinRunTime_API void Camera_SetTarget(CameraState* camera, Vector3 target);
MixinRunTime_API void Camera_SetUpVector(CameraState* camera, Vector3 up);
MixinRunTime_API void Camera_Move(CameraState* camera, Vector3 direction, double distance);
MixinRunTime_API void Camera_Rotate(CameraState* camera, double yaw, double pitch, double roll);
MixinRunTime_API void Camera_Zoom(CameraState* camera, double zoomDelta);
MixinRunTime_API void Camera_LookAt(CameraState* camera, Vector3 eye, Vector3 target, Vector3 up);

// ----------------- 投影设置 -----------------
MixinRunTime_API void Camera_SetPerspective(CameraState* camera, double fovY, double aspect, double nearPlane, double farPlane);
MixinRunTime_API void Camera_SetOrthographic(CameraState* camera, double left, double right, double bottom, double top, double nearPlane, double farPlane);
MixinRunTime_API void Camera_SetType(CameraState* camera, CameraType types);

// ----------------- 参数获取 -----------------
MixinRunTime_API Vector3 Camera_GetPosition(const CameraState* camera);
MixinRunTime_API Vector3 Camera_GetTarget(const CameraState* camera);
MixinRunTime_API Vector3 Camera_GetForward(const CameraState* camera);
MixinRunTime_API Vector3 Camera_GetRight(const CameraState* camera);
MixinRunTime_API Vector3 Camera_GetUp(const CameraState* camera);
MixinRunTime_API double Camera_GetFOV(const CameraState* camera);
MixinRunTime_API double Camera_GetAspectRatio(const CameraState* camera);
MixinRunTime_API CameraType Camera_GetType(const CameraState* camera);

// ----------------- 工具函数 -----------------
MixinRunTime_API void Camera_UpdateVectors(CameraState* camera);
MixinRunTime_API void Camera_UpdateMatrices(CameraState* camera);
MixinRunTime_API void Camera_MarkDirty(CameraState* camera);

