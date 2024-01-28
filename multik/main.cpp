// Copyright 2020 vorotynsky
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gl.h>

#include <iostream>
#include <fstream>

#include "render/VertexBuffer.hpp"
#include "render/IndexBuffer.hpp"
#include "render/VertexArray.hpp"
#include "types/reference.hpp"
#include "types/GLTypes.hpp"
#include "core/ShaderCache.hpp"
#include "platform/GlfwApplication.hpp"
#include "graphics/Renderer.hpp"
#include "graphics/common2d/Camera2D.hpp"
#include "graphics/common2d/PrimitiveShape.hpp"

namespace mltrender = multik::render;
namespace mltype = multik::types;
namespace mltg = multik::graphics;

class MainApp final : public multik::platform::GlfwApplication
{
protected:
    void Draw() override
    {
        renderer.ClearColor({0.1, 0.2, 0.3, 1.0f});
        renderer.Clear();
        renderer.Begin(camera);
        {
            renderer.Draw(*shape);
        }
        renderer.End();
    }

    void Init() override
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

        auto square = multik::MakeRef<mltrender::VertexArray>();

        mltrender::BufferLayout layout({
            mltrender::BufferElement::createBuffer<mltype::Float2>()
        });

        auto vb = multik::MakeRef<mltrender::VertexBuffer>(vertices, 4 * 2 * sizeof(float), layout);
        auto ib = multik::MakeRef<mltrender::IndexBuffer>(indeces, 6);

        square->AppendVertexBuffer(vb);
        square->ResetIndexBuffer(ib);

        shape = multik::MakeUniq<mltg::common2d::PrimitiveShape>(square, shader);
    }

public:
    static const int ScreenWidth = 1280, ScreenHeight = 720;

    MainApp()
        : multik::platform::GlfwApplication(ScreenWidth, ScreenHeight)
        {
            const float yBorder = 2.0f * ScreenHeight / ScreenWidth;
            camera = multik::MakeRef<mltg::common2d::Camera2D>(-2.0, 2.0, -yBorder, yBorder);
        }

    MainApp(const MainApp &other) = delete;

    virtual ~MainApp() = default;

private:
    mltg::Renderer renderer;
    multik::Ref<mltg::Camera> camera;
    multik::Uniq<mltg::Shape> shape;
};

int main(const int argc, const char **argv)
{
    MainApp app;
    app.Run();
    return 0;
}
