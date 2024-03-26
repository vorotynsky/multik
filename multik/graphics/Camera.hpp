#pragma once

#include <gl.h>
#include "Shape.hpp"

namespace multik::graphics
{
    class Camera
    {
    protected:
        Camera() = default;
        
    public:
        virtual ~Camera() = default;
        
        virtual glm::mat4 getMVPMatrix(const glm::mat4 &model) const = 0;
        virtual glm::mat4 getMVPMatrix(const Shape     &shape) const
        {
            return getMVPMatrix(shape.getModelMatrix());
        }
        
        virtual void setViewMatrix(const glm::mat4 &matrix) = 0;
        virtual void setProjMatrix(const glm::mat4 &matrix) = 0;
    };
}
