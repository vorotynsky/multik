// Copyright (c) 2020 Vorotynsky Maxim

#include "Camera2D.hpp"

namespace multik::graphics::common2d
{
    Camera2D::Camera2D(float left, float top, float right, float bottom)
        : view(1.0f), proj(glm::ortho(left, top, right, bottom)) { }

    glm::mat4 Camera2D::getMVPMatrix(const glm::mat4 &model) const
    {
        return this->proj * this->view * model;
    }
    
    void Camera2D::setViewMatrix(const glm::mat4 &matrix)
    {
        this->view = matrix;
    }
    void Camera2D::setProjMatrix(const glm::mat4 &matrix)
    {
        this->proj = matrix;
    }
}
