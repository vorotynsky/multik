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

#include <gl.h>
#include "VertexArray.hpp"
#include "../types/GLTypes.hpp"

namespace multik::core
{
    VertexArray::VertexArray()
        : indexBuffer(nullptr), vertexBuffers(), vertexBufferId(0)
    {
        glGenVertexArrays(1, &this->id);
        this->Bind();
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &this->id);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(this->id);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    const Ref<IndexBuffer> &VertexArray::getIndexBuffer() const
    {
        return this->indexBuffer;
    }

    const std::vector<Ref<VertexBuffer>> &VertexArray::getVertexBuffers() const
    {
        return this->vertexBuffers;
    }

    void VertexArray::AppendVertexBuffer(const Ref<VertexBuffer> &buffer)
    {

        this->Bind();
        buffer->Bind();

        this->vertexBuffers.push_back(buffer);
        AppendLayout(buffer);
    }

    void VertexArray::ResetIndexBuffer(const Ref<IndexBuffer> &buffer)
    {
        this->Bind();
        buffer->Bind();

        this->indexBuffer = buffer;
    }

    void VertexArray::AppendLayout(const Ref<VertexBuffer> &buffer)
    {
        auto layout = buffer->getLayout();
        for (auto &element : layout)
        {
            glEnableVertexAttribArray(vertexBufferId);

            glVertexAttribPointer(vertexBufferId, 
                element.Type.Count, 
                types::gl::toEnum(element.Type.Type),
                types::gl::boolean(element.Normalized), 
                layout.getStride(),
                (GLvoid*) element.Offset);

            vertexBufferId += 1;
        }
    }
}
