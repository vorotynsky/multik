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
        PrimitiveShape(const Ref<render::VertexArray> va, const Ref<render::Shader> &shader, render::DrawCall pen);
        virtual ~PrimitiveShape() = default;

        int IndexCount() const override;
        const glm::mat4 &getModelMatrix() const override;
        void setModelMatrix(const glm::mat4 &matrix) override;

        void setMVP(const glm::mat4 &mvp) override;
        render::DrawCall Pen() const override;

        void Bind() override;
        void Unbind() override;

    private:
        render::DrawCall pen;
        glm::mat4 model;
        Ref<render::Shader> shader;
        Ref<render::VertexArray> array;
    };
}
