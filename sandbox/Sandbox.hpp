// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <multik/types/reference.hpp>
#include <multik/platform/GlfwApplication.hpp>
#include <multik/graphics/Camera.hpp>
#include <multik/graphics/Renderer.hpp>

#include "Scene.hpp"
#include "Parser.hpp"

namespace mltg = multik::graphics;

class SandboxApp final : public multik::platform::GlfwApplication
{
protected:
    void Draw() override;
    void Init() override;

public:
    SandboxApp();
    SandboxApp(const SandboxApp &other) = delete;
    virtual ~SandboxApp() = default;

private:
    bool swaped = false;
    Scene scene;
    CommandParser parser;
    mltg::Renderer renderer;
    multik::Ref<mltg::Camera> camera;
};
