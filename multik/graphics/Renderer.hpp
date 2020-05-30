// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <gl.h>

#include "Shape.hpp"
#include "Camera.hpp"
#include "../render/VertexArray.hpp"
#include "../render/Shader.hpp"

namespace multik::graphics 
{
    class Renderer
    {
    public:
        void ClearColor(const glm::vec4 &color);
        void Clear();

        void Begin(const Ref<Camera> &camera);
        void End();

        void Draw(render::VertexArray &array, render::Shader &shader, render::DrawCall pen);
        void Draw(Shape &shape);
    private:
        Ref<Camera> activeCamera;  
    };
}
