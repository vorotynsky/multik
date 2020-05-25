// Copyright (c) 2020 Vorotynsky Maxim

#include "Renderer.hpp"

namespace multik::graphics 
{
    void Renderer::Draw(render::VertexArray &array, render::Shader &shader, render::DrawCall pen)
    {
        shader.Bind();
        array.Bind();

        pen.Draw(array.getIndexBuffer()->Count());

        array.Unbind();
        shader.Unbind();
    }

    void Renderer::Draw(Shape &shape)
    {
        shape.Bind();
        
        auto mvp = activeCamera->getMVPMatrix(shape.getModelMatrix());
        shape.setMVP(mvp);
        shape.Pen().Draw(shape.IndexCount());
        
        shape.Unbind();
    }

    void Renderer::Begin(const Ref<Camera> &camera)
    {
        this->activeCamera = camera;
    }

    void Renderer::End()
    {
        activeCamera.reset();
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
