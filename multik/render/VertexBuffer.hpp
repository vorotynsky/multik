#pragma once

#include "../types/numeric.hpp"
#include "VertexLayout.hpp"

namespace multik::render
{
    class VertexBuffer
    {
    public:
        VertexBuffer(const void *data, types::ssize_t size, const BufferLayout &layout);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer &other) = delete;

        const BufferLayout &getLayout() const;

        void Bind();
        void Unbind();

    private:
        unsigned int id;
        BufferLayout layout;
    };
}
