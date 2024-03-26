#include "VertexLayout.hpp"

namespace multik::render
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
