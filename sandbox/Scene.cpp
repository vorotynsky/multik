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
    auto shape = dynamic_cast<const ConstructCommand*>(command);
    
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
    else if (shape != nullptr)
    {
        data[shape->getName()] = shape->shape();
        return;
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
