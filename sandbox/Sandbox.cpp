// Copyright (c) 2020 Vorotynsky Maxim

#include "Sandbox.hpp"

#include <multik/entry.hpp>
#include <multik/core/ShaderCache.hpp>
#include <multik/graphics/common2d/Camera2D.hpp>
#include <multik/graphics/common2d/PrimitiveShape.hpp>


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

    auto shader = multik::core::ShaderCache::Get("square/color");

    float vertices[4 * 2] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };
    unsigned int indeces[6] = {
        0, 1, 2,
        2, 3, 0
    };

    auto square = multik::MakeRef<multik::render::VertexArray>();

    multik::render::BufferLayout layout({
        multik::render::BufferElement::createBuffer<multik::types::Float2>()
    });

    auto vb = multik::MakeRef<multik::render::VertexBuffer>(vertices, 4 * 2 * sizeof(float), layout);
    auto ib = multik::MakeRef<multik::render::IndexBuffer>(indeces, 6);

    square->AppendVertexBuffer(vb);
    square->ResetIndexBuffer(ib);

    shape = multik::MakeUniq<mltg::common2d::PrimitiveShape>(square, shader);
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
