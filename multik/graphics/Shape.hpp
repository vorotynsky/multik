// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <gl.h>

#include "../render/DrawCall.hpp"

namespace multik::graphics
{
    class Shape
    {
    protected:
        Shape() = default;
    public:
        virtual ~Shape() = default;

        virtual const glm::mat4 &getModelMatrix() const = 0;
        virtual void setModelMatrix(const glm::mat4 &matrix) = 0;

        virtual void setMVP(const glm::mat4 &mvp) = 0;
        virtual render::DrawCall Pen() const = 0;
        virtual int  IndexCount() const = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };
}
