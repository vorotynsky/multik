// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include "../Camera.hpp"

namespace multik::graphics::common2d
{
    class Camera2D : public Camera
    {
    public:
        Camera2D(float left, float top, float right, float bottom);
        virtual ~Camera2D() = default;

        glm::mat4 getMVPMatrix(const glm::mat4 &model) const override;
        
        void setViewMatrix(const glm::mat4 &matrix) override;
        void setProjMatrix(const glm::mat4 &matrix) override;
    private:
        glm::mat4 view;    
        glm::mat4 proj;
    };
}
