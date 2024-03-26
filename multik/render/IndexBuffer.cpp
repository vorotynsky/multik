#include <gl.h>
#include "IndexBuffer.hpp"

namespace multik::render
{
    IndexBuffer::IndexBuffer(const unsigned int *indexes, unsigned short count)
        : count(count)
    {
        static_assert(sizeof(unsigned int) == sizeof(GLuint), "[Index Buffer] GLuint isn't unsigned int. ");

        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indexes, GL_STATIC_DRAW);

    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &id);
    }

    void IndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    types::ssize_t IndexBuffer::Count() const
    {
        return this->count;
    }
}
