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
