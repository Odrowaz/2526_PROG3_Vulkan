#pragma once
#include "Transform.h"

class Camera: public Transform {
public:
    Camera(float InFOV, float InAspectRatio, float InNearPlane, float InFarPlane)
        : FOV(InFOV), AspectRatio(InAspectRatio), NearPlane(InNearPlane), FarPlane(InFarPlane) {}
    glm::mat4 GetProjectionMatrix() const;
    glm::mat4 GetViewMatrix() const;

    void SetAspectRatio(float InAspectRatio) { AspectRatio = InAspectRatio; }
    void SetFOV(float InFOV) { FOV = InFOV; }
protected:
    float FOV;
    float AspectRatio;
    float NearPlane;
    float FarPlane;
};