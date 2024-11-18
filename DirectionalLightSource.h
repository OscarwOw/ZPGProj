#pragma once

#include "ILightEmitter.h"
#include "LightType.h"
#include <glm/glm.hpp>

class DirectionalLightSource : public ILightEmitter {
private:
    glm::vec4 _lightColor; 
    glm::vec3 _direction;  
    float _lightIntensity;

public:

    DirectionalLightSource( glm::vec3 direction, glm::vec4 color = glm::vec4(1.0f), float intensity = 1.0f)
        : _direction(glm::normalize(direction)), _lightColor(color), _lightIntensity(intensity) {
    }

    void setDirection( glm::vec3& direction);
    glm::vec3 getDirection() ;

    void setLightColor( glm::vec4& color);
    glm::vec4 getLightColor() ;

    void setLightIntensity(float intensity);
    float getLightIntensity() ;

    LightData getLightData()  override;
};
