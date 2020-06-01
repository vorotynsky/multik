// Copyright (c) 2020 Vorotynsky Maxim

#include "Scene.hpp"

#include <multik/graphics/common2d/PrimitiveShape.hpp>
#include <multik/render/DrawCall.hpp>
#include <multik/core/ShaderCache.hpp>
#include <multik/render/VertexLayout.hpp>


void Scene::DrawAll(multik::graphics::Renderer &renderer)
{
    for (auto &item : data)
        renderer.Draw(*item.second);
}

void Scene::Apply(const ICommand *command)
{
    auto undo = dynamic_cast<const Undo*>(command);
    auto matr = dynamic_cast<const Command*>(command);
    
    Command cmd;
    if (undo != nullptr)
    {
        cmd = history.top();
        history.pop();
        cmd.reverse();
    }
    else if (matr != nullptr)
    {
        cmd = *matr;
        history.push(cmd);
    }
    else
    {
        throw std::string("unexpected command");
    }    

    auto it = data.find(cmd.getName());
    if (it == data.end())
        throw std::string("unexpected command");
    auto model = it->second->getModelMatrix();
    model = model * cmd.getMatrix();
    it->second->setModelMatrix(model);
}

void Scene::AppendLine(const std::string &name, float x, float y, float w, float h)
{
    float arr[] = {x, y, x + w, y + h};
    unsigned int i[] = {0, 1};
    
    multik::render::BufferLayout layout({
        multik::render::BufferElement::createBuffer<multik::types::Float2>()
    });

    auto vb = multik::MakeRef<multik::render::VertexBuffer>(arr, 4 * sizeof(float), layout);
    auto ib = multik::MakeRef<multik::render::IndexBuffer>(i, 2);

    Append(name, "square/color", vb, ib, multik::render::DrawCall::Lines());
}
void Scene::AppendRect(const std::string &name, float x, float y, float w, float h)
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

    Append(name, "square/color", vb, ib, multik::render::DrawCall::Triangles());
}

void Scene::Append(const std::string &name, const std::string &shader,       
        const multik::Ref<multik::render::VertexBuffer> &vb, 
        const multik::Ref<multik::render::IndexBuffer> &ib,
        multik::render::DrawCall pen)
{
    auto s = multik::core::ShaderCache::Get(shader);
    auto array = multik::MakeRef<multik::render::VertexArray>();

    array->AppendVertexBuffer(vb);
    array->ResetIndexBuffer(ib);

    data.emplace(name, multik::MakeUniq<multik::graphics::common2d::PrimitiveShape>(array, s, pen));
}
