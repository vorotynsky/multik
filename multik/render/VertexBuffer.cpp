#include <gl.h>
#include "VertexBuffer.hpp"

namespace multik::render 
{
    VertexBuffer::VertexBuffer(const void *data, unsigned short size, const BufferLayout &layout)
        : layout(layout)
    {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &id);
    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
    }

    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    const BufferLayout &VertexBuffer::getLayout() const
    {
        return this->layout;
    }
}
