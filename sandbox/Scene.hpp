// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <map>
#include <stack>
#include <multik/graphics/Renderer.hpp>

#include "Command.hpp"

class Scene
{
public:
    void DrawAll(multik::graphics::Renderer &renderer);
    void Apply(const ICommand *cmd);

private:
    void Append(const std::string &name, const std::string &shader,
        const multik::Ref<multik::render::VertexBuffer> &vb, 
        const multik::Ref<multik::render::IndexBuffer> &ib,
        multik::render::DrawCall pen);

    std::map<std::string, multik::Uniq<multik::graphics::Shape>> data;
    std::stack<Command> history;
};
