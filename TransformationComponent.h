// TransformationComponent.h
#pragma once

class TransformationComponent {
public:
    virtual void markDirty() = 0; // Pure virtual function
    virtual ~TransformationComponent() = default; // Virtual destructor
};
