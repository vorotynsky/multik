// Copyright (c) 2020 Vorotynsky Maxim

#include "Sandbox.hpp"

#include <multik/entry.hpp>
#include <multik/core/ShaderCache.hpp>
#include <multik/graphics/common2d/Camera2D.hpp>
#include <multik/graphics/common2d/Ellipse.hpp>


void SandboxApp::Draw()
{
    renderer.ClearColor({0.1, 0.2, 0.3, 1.0});
    renderer.Clear();
    renderer.Begin(camera);
    {
        renderer.Draw(*shape);
    }
    renderer.End();
}

void SandboxApp::Init()
{
    multik::platform::GlfwApplication::Init();

    shape = multik::MakeUniq<mltg::common2d::Ellipse>(glm::vec4(0.192f, 0.96f, 0.512f, 1.0f));
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
