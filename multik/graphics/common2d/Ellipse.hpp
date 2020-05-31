// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include "../Shape.hpp"
#include "../../render/VertexArray.hpp"
#include "../../render/Shader.hpp"

namespace multik::graphics::common2d
{
    class Ellipse final : public Shape
    {
    public:
        Ellipse(const glm::vec4 &color);
        virtual ~Ellipse() = default;

        const glm::mat4 &getModelMatrix() const override;
        void setModelMatrix(const glm::mat4 &matrix) override;

        void setMVP(const glm::mat4 &mvp) override;
        render::DrawCall Pen() const override;
        int IndexCount() const override;

        void Bind() override;
        void Unbind() override;

    private:
        static void Init();

        static Ref<render::Shader> shader;
        static Uniq<render::VertexArray> array;
        glm::mat4 model;
        glm::vec4 color;
    };
}
