// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <gl.h>

namespace multik::graphics
{
    class Camera
    {
    protected:
        Camera() = default;
        
    public:
        virtual ~Camera() = default;
        
        virtual glm::mat4 getMVPMatrix(const glm::mat4 &model) const = 0;
        
        virtual void setViewMatrix(const glm::mat4 &matrix) = 0;
        virtual void setProjMatrix(const glm::mat4 &matrix) = 0;
    };
}
