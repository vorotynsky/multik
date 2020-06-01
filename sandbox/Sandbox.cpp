// Copyright (c) 2020 Vorotynsky Maxim

#include "Sandbox.hpp"

#include <multik/entry.hpp>
#include <multik/graphics/common2d/Camera2D.hpp>


void SandboxApp::Draw()
{
    renderer.ClearColor({0.1, 0.2, 0.3, 1.0});
    renderer.Clear();
    renderer.Begin(camera);
    {
        scene.DrawAll(renderer);
    }
    renderer.End();
}

void SandboxApp::Init()
{
    multik::platform::GlfwApplication::Init();

    scene.AppendLine("line1", -2.0, -1.5,  4.0, 3.0);
    scene.AppendLine("line2",  2.0, -1.5, -4.0, 3.0);
    scene.AppendRect("rect1", -1.0, -0.75, 2.0, 1.5);
}

SandboxApp::SandboxApp()
    : multik::platform::GlfwApplication(640, 480)
{
    camera = multik::MakeRef<mltg::common2d::Camera2D>(-2.0, 2.0, -1.5, 1.5);
}


typename multik::core::Application *multik::MainApplication()
{
    return new SandboxApp();
}
