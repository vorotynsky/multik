// Copyright (c) 2020 Vorotynsky Maxim

#include "Sandbox.hpp"

#include <multik/entry.hpp>
#include <multik/graphics/common2d/Camera2D.hpp>


void SandboxApp::Draw()
{
    if (swaped)
    {
        auto cmd = parser.next();
        scene.Apply(cmd);
        delete cmd;
    }

    renderer.ClearColor({0.1, 0.2, 0.3, 1.0});
    renderer.Clear();
    renderer.Begin(camera);
    {
        scene.DrawAll(renderer);
    }
    renderer.End();
    swaped = !swaped;  
}

void SandboxApp::Init()
{
    multik::platform::GlfwApplication::Init();
}

SandboxApp::SandboxApp()
    : multik::platform::GlfwApplication(640, 480), parser(std::cin)
{
    camera = multik::MakeRef<mltg::common2d::Camera2D>(-2.0, 2.0, -1.5, 1.5);
}


typename multik::core::Application *multik::MainApplication()
{
    return new SandboxApp();
}
