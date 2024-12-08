#pragma once
#include "Transformation.h"

class TransformationBezier : public Transformation, public IAnimationObject {
private:
    glm::mat4 _matrix;
    std::vector<glm::vec3> _controlPoints;
    float t;
    float speed;

public:
    TransformationBezier(
        const glm::mat4& initialMatrix,
        const std::vector<glm::vec3>& points,
        float speed = 0.5f
    )
        : _matrix(initialMatrix), _controlPoints(points), t(0.0f), speed(speed)
    {
    }

    void update(float deltaTime) override {
        t += speed * deltaTime;

        while (t > 1.0f) {
            t -= 1.0f;
        }

        internalUpdate();
    }

    glm::mat4 getMatrix() override {
        return _matrix;
    }

private:
    void internalUpdate() {
        glm::vec3 position = generalBezierPoint(t);
        _matrix = glm::translate(glm::mat4(1.0f), position);
    }

    unsigned int binomialCoefficient(unsigned int n, unsigned int k) {
        if (k > n) return 0;
        if (k == 0 || k == n) return 1;
        unsigned int result = 1;
        for (unsigned int i = 1; i <= k; ++i) {
            result = result * (n - (k - i)) / i;
        }
        return result;
    }

    glm::vec3 generalBezierPoint(float t) {
        glm::vec3 result(0.0f);
        size_t n = _controlPoints.size();
        if (n == 0) return result;

        for (size_t i = 0; i < n; ++i) {
            unsigned int c = binomialCoefficient(static_cast<unsigned int>(n - 1), static_cast<unsigned int>(i));
            float blend = c * std::pow(1.0f - t, (float)(n - 1 - i)) * std::pow(t, (float)i);
            result += blend * _controlPoints[i];
        }

        return result;
    }
};