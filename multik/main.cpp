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
#include "render/Shader.hpp"
#include "types/reference.hpp"
#include "types/GLTypes.hpp"
#include "platform/GlfwApplication.hpp"
#include "graphics/Renderer.hpp"

namespace mltrender = multik::render;
namespace mltype = multik::types;

class MainApp final : public multik::platform::GlfwApplication
{
protected:
    void Draw() override
    {
        renderer.Draw(*square, *shader);
    }

    void Init() override
    {
        multik::platform::GlfwApplication::Init();

        shader = mltrender::Shader::ReadFiles(
                "shaders/square/color.vertex.glsl",
                "shaders/square/color.fragment.glsl"
            );
        
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

        square = multik::MakeUniq<mltrender::VertexArray>();

        mltrender::BufferLayout layout({
            mltrender::BufferElement::createBuffer<mltype::Float2>()
        });

        auto vb = multik::MakeRef<mltrender::VertexBuffer>(vertices, 4 * 2 * sizeof(float), layout);
        auto ib = multik::MakeRef<mltrender::IndexBuffer>(indeces, 6);

        square->AppendVertexBuffer(vb);
        square->ResetIndexBuffer(ib);
    }

public:
    MainApp() 
        : multik::platform::GlfwApplication(640, 480), renderer() { }

    MainApp(const MainApp &other) = delete;

    virtual ~MainApp() = default;

private:
    multik::Uniq<multik::render::VertexArray> square;
    multik::Ref<multik::render::Shader> shader;
    multik::graphics::Renderer renderer;
};

int main(const int argc, const char **argv)
{
    MainApp app;
    app.Run();
    return 0;
}
