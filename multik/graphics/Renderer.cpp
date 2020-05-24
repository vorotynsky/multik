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

    void Renderer::Begin(const Ref<Camera> &camera)
    {
        this->activeCamera = camera;
    }

    void Renderer::End()
    {
        activeCamera.reset();
    }


    void Renderer::Draw(Shape &shape)
    {
        shape.Bind();
        auto mvp = activeCamera->getMVPMatrix(shape.getModelMatrix());
        shape.setMVP(mvp);
        glDrawElements(GL_TRIANGLES, shape.IndexCount(), GL_UNSIGNED_INT, nullptr);
        shape.Unbind();
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
