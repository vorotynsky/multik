// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <gl.h>

#include "../render/IndexBuffer.hpp"
#include "../render/VertexArray.hpp"
#include "../render/Shader.hpp"

namespace multik::graphics 
{
    class Renderer
    {
    public:
        void ClearColor(const glm::vec4 &color);
        void Clear();

        void Draw(render::VertexArray &array, render::Shader &shader);
    };
}
