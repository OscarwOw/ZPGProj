#pragma once
#include <glm/ext/vector_float3.hpp>
struct MaterialProperties {
    glm::vec3 ambientReflectivity;    // Ambient reflectivity (r_a)
    glm::vec3 diffuseReflectivity;    // Diffuse reflectivity (r_d)
    glm::vec3 specularReflectivity;   // Specular reflectivity (r_s)
    float shininess;                  // Shininess factor (s)

    MaterialProperties(
        glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f),
        float shininessValue = 32.0f
    )
        : ambientReflectivity(ambient),
        diffuseReflectivity(diffuse),
        specularReflectivity(specular),
        shininess(shininessValue) {
    }
};
