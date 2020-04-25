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

#include "VertexLayout.hpp"

namespace multik::core
{
    BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements)
        : elements(elements), stride(0) 
    {
        evaluate();
    }

    typename std::vector<BufferElement>::const_iterator BufferLayout::begin() const
    {
        return elements.cbegin();
    }
    
    typename std::vector<BufferElement>::const_iterator BufferLayout::end() const
    {
        return elements.end();
    }

    void BufferLayout::evaluate()
    {
        int offset = 0;
        for (auto &el : elements)
        {
            el.Offset = offset;
            offset += el.Type.Size;
            stride += el.Type.Size;
        }
    }

    uint32_t BufferLayout::getStride() const
    {
        return this->stride;
    }
}
