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
