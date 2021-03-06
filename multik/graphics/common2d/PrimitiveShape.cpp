// Copyright (c) 2020 Vorotynsky Maxim

#include "PrimitiveShape.hpp"

namespace multik::graphics::common2d
{
    PrimitiveShape::PrimitiveShape(const Ref<render::VertexArray> va, const Ref<render::Shader> &shader)
        : model(1.0f), array(va), shader(shader), pen() { }

    PrimitiveShape::PrimitiveShape(const Ref<render::VertexArray> va, const Ref<render::Shader> &shader, render::DrawCall pen)
        : model(1.0f), array(va), shader(shader), pen(pen) { }

    int PrimitiveShape::IndexCount() const
    {
        return this->array->getIndexBuffer()->Count();
    }

    const glm::mat4 &PrimitiveShape::getModelMatrix() const
    {
        return this->model;
    }
    
    void PrimitiveShape::setModelMatrix(const glm::mat4 &matrix)
    {
        this->model = matrix;
    }

    void PrimitiveShape::setMVP(const glm::mat4 &mvp)
    {
        shader->SetUniform("u_mvp", mvp);
    }

    typename render::DrawCall PrimitiveShape::Pen() const
    {
        return this->pen;
    }

    void PrimitiveShape::Bind()
    {
        array->Bind();
        shader->Bind();
    }

    void PrimitiveShape::Unbind()
    {
        shader->Unbind();
        array->Unbind();
    }
}
