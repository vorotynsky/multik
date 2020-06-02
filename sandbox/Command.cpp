// Copyright (c) 2020 Vorotynsky Maxim

#include "Command.hpp"
#include <gl.h>
#include <multik/graphics/common2d/PrimitiveShape.hpp>
#include <multik/graphics/common2d/Ellipse.hpp>
#include <multik/render/DrawCall.hpp>
#include <multik/core/ShaderCache.hpp>
#include <multik/render/VertexLayout.hpp>

Command *Command::transform(const std::string &name, float x, float y)
{
    auto cmd = new Command();
    cmd->matrix = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0.0f));
    cmd->name = name;
    return cmd;
}

Command *Command::scale(const std::string &name, float x, float y)
{
    auto cmd = new Command();
    cmd->matrix = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, 1.0f));
    cmd->name = name;
    return cmd;
}

Command *Command::rotate(const std::string &name, float angle)
{
    auto cmd = new Command();
    cmd->matrix = glm::rotate(glm::mat4(1.0f), angle / 180.0f * 3.14f, glm::vec3(0, 0, 1));
    cmd->name = name;
    return cmd;
}

void Command::reverse()
{
    matrix = glm::inverse(matrix);
}

const std::string &Command::getName() const
{
    return this->name;
}

const glm::mat4 &Command::getMatrix() const
{
    return this->matrix;
}

const std::string &ConstructCommand::getName() const
{
    return this->name;
}

ConstructCommand::ConstructCommand(const std::string &name) : name(name) { }
ConstructLine::ConstructLine(const std::string &name, float x, float y, float w, float h) 
    : ConstructCommand(name), x(x), y(y), w(w), h(h) { }
ConstructRect::ConstructRect(const std::string &name, float x, float y, float w, float h) 
    : ConstructCommand(name), x(x), y(y), w(w), h(h) { }
ConstructEllipse::ConstructEllipse(const std::string &name) : ConstructCommand(name) { }

typename multik::Uniq<multik::graphics::Shape> genShape(
    const std::string &shader,
    const multik::Ref<multik::render::VertexBuffer> &vb, 
    const multik::Ref<multik::render::IndexBuffer> &ib,
    multik::render::DrawCall pen)
{
    auto s = multik::core::ShaderCache::Get(shader);
    auto array = multik::MakeRef<multik::render::VertexArray>();

    array->AppendVertexBuffer(vb);
    array->ResetIndexBuffer(ib);

    return multik::MakeUniq<multik::graphics::common2d::PrimitiveShape>(array, s, pen);
}

typename multik::Uniq<multik::graphics::Shape> ConstructLine::shape() const
{
    float arr[] = {x, y, x + w, y + h};
    unsigned int i[] = {0, 1};
    
    multik::render::BufferLayout layout({
        multik::render::BufferElement::createBuffer<multik::types::Float2>()
    });

    auto vb = multik::MakeRef<multik::render::VertexBuffer>(arr, 4 * sizeof(float), layout);
    auto ib = multik::MakeRef<multik::render::IndexBuffer>(i, 2);

    return genShape("square/color", vb, ib, multik::render::DrawCall::Lines());
}

typename multik::Uniq<multik::graphics::Shape> ConstructRect::shape() const
{
    float arr[] = {
        x,     y,
        x + w, y,
        x + w, y + h,
        x,     y + h
    };
    unsigned int i[] = {0, 1, 2,   2, 3, 0};
    
    multik::render::BufferLayout layout({
        multik::render::BufferElement::createBuffer<multik::types::Float2>()
    });

    auto vb = multik::MakeRef<multik::render::VertexBuffer>(arr, 8 * sizeof(float), layout);
    auto ib = multik::MakeRef<multik::render::IndexBuffer>(i, 6);

    return genShape("square/color", vb, ib, multik::render::DrawCall::Triangles());
}

typename multik::Uniq<multik::graphics::Shape> ConstructEllipse::shape() const
{
    return multik::MakeUniq<multik::graphics::common2d::Ellipse>(glm::vec4(0.192f, 0.96f, 0.512f, 1.0f));
}
