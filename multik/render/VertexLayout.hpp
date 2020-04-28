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
#include <cstdint>
#include <initializer_list>
#include "../types/Graphics.hpp"

namespace multik::render
{
    struct BufferElement
    {
        multik::types::GraphicsTypeInfo Type;
        std::size_t Offset;
        bool Normalized;

        template <typename Type>
        static BufferElement createBuffer(bool normalized = false)
        {
            return { Type::info(), 0, normalized };
        }
    };

    class BufferLayout 
    {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement> &elements);

        std::vector<BufferElement>::const_iterator begin() const;
        std::vector<BufferElement>::const_iterator end() const;

        uint32_t getStride() const;

    private:
        void evaluate();
        uint32_t stride;
        std::vector<BufferElement> elements;
    };
}
