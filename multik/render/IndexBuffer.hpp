#pragma once

#include "../types/numeric.hpp"

namespace multik::render
{
    class IndexBuffer
    {
    public:
        IndexBuffer(const unsigned int *indexes, types::ssize_t count);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer &other) = delete;

        void Bind();
        void Unbind();

        types::ssize_t Count() const;

    private:
        unsigned int id;
        types::ssize_t count;
    };
}
