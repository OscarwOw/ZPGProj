#pragma once
class IAnimationObject {
public:
    virtual ~IAnimationObject() = default;

    virtual void update(float deltaTime) = 0;
};