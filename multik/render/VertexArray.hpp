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

#include <vector>
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexLayout.hpp"
#include "../types/reference.hpp"

namespace multik::render
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray &other) = delete;

        void Bind();
        void Unbind();

        const Ref<IndexBuffer> &getIndexBuffer() const;
        const std::vector<Ref<VertexBuffer>> &getVertexBuffers() const;

        void AppendVertexBuffer(const Ref<VertexBuffer> &buffer);
        void ResetIndexBuffer(const Ref<IndexBuffer> &buffer);

    private:
        void AppendLayout(const Ref<VertexBuffer> &buffer);

        unsigned int id;
        unsigned int vertexBufferId;
        Ref<IndexBuffer> indexBuffer;
        std::vector<Ref<VertexBuffer>> vertexBuffers;
    };
}
