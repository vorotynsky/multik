// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <gl.h>

#include "../Shape.hpp"
#include "../../types/reference.hpp"
#include "../../render/VertexArray.hpp"
#include "../../render/Shader.hpp"

namespace multik::graphics::common2d
{
    class PrimitiveShape : public Shape
    {
    public:
        PrimitiveShape(const Ref<render::VertexArray> va, const Ref<render::Shader> &shader);
        virtual ~PrimitiveShape() = default;

        int IndexCount() const override;
        const glm::mat4 &getModelMatrix() const override;
        void setModelMatrix(const glm::mat4 &matrix) override;

        void setMVP(const glm::mat4 &mvp) override;

        void Bind() override;
        void Unbind() override;

    private:
        glm::mat4 model;
        Ref<render::Shader> shader;
        Ref<render::VertexArray> array;
    };
}
