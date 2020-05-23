// Copyright (c) 2020 Vorotynsky Maxim

#include <gl.h>
#include "Renderer.hpp"

namespace multik::graphics 
{
    void Renderer::Draw(render::VertexArray &array, render::Shader &shader)
    {
        shader.Bind();
        array.Bind();

        glDrawElements(GL_TRIANGLES, array.getIndexBuffer()->Count(), GL_UNSIGNED_INT, nullptr);

        array.Unbind();
        shader.Unbind();
    }    

    void Renderer::ClearColor(const glm::vec4 &color) 
    {
        glClearColor(color.r, color.g, color.b, color.a);

    }
    void Renderer::Clear() 
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
