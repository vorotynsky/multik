// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <map>
#include <multik/graphics/Renderer.hpp>

class Scene
{
public:
    void DrawAll(multik::graphics::Renderer &renderer);

    void AppendLine(const std::string &name, float x, float y, float w, float h);
    void AppendRect(const std::string &name, float x, float y, float w, float h);
private:
    void Append(const std::string &name, const std::string &shader,
        const multik::Ref<multik::render::VertexBuffer> &vb, 
        const multik::Ref<multik::render::IndexBuffer> &ib,
        multik::render::DrawCall pen);

    std::map<std::string, multik::Uniq<multik::graphics::Shape>> data;
};
