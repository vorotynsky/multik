// Copyright (c) 2020 Vorotynsky Maxim

#include "Ellipse.hpp"
#include "../../core/ShaderCache.hpp"
#include <iostream>

namespace multik::graphics::common2d {
    Ellipse::Ellipse(const glm::vec4 &color) 
        : color(color), model(1.0f) 
    {
        Init();
    }

    Ref<render::Shader> Ellipse::shader;
    Uniq<render::VertexArray> Ellipse::array;

    void Ellipse::Init()
    {
        if (shader)
            return;
        shader = core::ShaderCache::Get("ellipse");
        array = MakeUniq<render::VertexArray>();
        {
            float vertecies[] = {
                 1.0f,  1.0f, 
                 1.0f, -1.0f,
                -1.0f, -1.0f,
                -1.0f,  1.0f
            };
            unsigned int indecies[] = { 0, 1, 2, 2, 3, 0 };

            render::BufferLayout layout({
                    render::BufferElement::createBuffer<types::Float2>()
            });

            auto vb = multik::MakeRef<render::VertexBuffer>(vertecies, 8 * sizeof(float), layout);
            auto ib = multik::MakeRef<render::IndexBuffer>(indecies, 6);

            array->AppendVertexBuffer(vb);
            array->ResetIndexBuffer(ib);
        }
    }

    const glm::mat4 &Ellipse::getModelMatrix() const 
	{
        return this->model;
	}

    void Ellipse::setModelMatrix(const glm::mat4 &matrix) 
	{
        this->model = matrix;
	}

    void Ellipse::setMVP(const glm::mat4 &mvp) 
	{
        shader->SetUniform("u_mvp", mvp);
	}

    render::DrawCall Ellipse::Pen() const 
	{
        return render::DrawCall::Triangles();
	}

    int Ellipse::IndexCount() const 
	{
        return 6;
    }

    void Ellipse::Bind() 
    {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        
        shader->Bind();
        shader->SetUniform("u_color", color);
        shader->SetUniform("u_resolution", glm::vec2(viewport[2], viewport[3]));
        array->Bind();
	}

    void Ellipse::Unbind() 
	{
        array->Unbind();
        array->Unbind();
	}
}

