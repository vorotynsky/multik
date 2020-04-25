// Copyright 2020 Vorotynsky Maxim
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

#pragma once

#include <gl.h>

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

namespace multik::core 
{
    class Renderer
    {
    public:
        void Draw(VertexArray &array, Shader &shader)
        {
            shader.Bind();
            array.Bind();

            Renderer::glCall(array.getIndexBuffer()->Count());

            array.Unbind();
            shader.Unbind();
        }
        void Draw(VertexArray &array, IndexBuffer &index, Shader &shader)
        {
            shader.Bind();
            array.Bind();
            index.Bind();

            Renderer::glCall(index.Count());

            index.Unbind();
            array.Unbind();
            shader.Unbind();
        }
    private:
        inline static void glCall(unsigned int count)
        {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }
    };
}
