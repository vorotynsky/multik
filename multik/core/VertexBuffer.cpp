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

#include <GL/glew.h>
#include "VertexBuffer.hpp"


multik::core::VertexBuffer::VertexBuffer(const void *data, unsigned short size)
{
    glGenBuffers(1, &this->id);
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

multik::core::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

void multik::core::VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void multik::core::VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
