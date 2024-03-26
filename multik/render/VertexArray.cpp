#include <gl.h>
#include "VertexArray.hpp"
#include "../types/GLTypes.hpp"

namespace multik::render
{
    VertexArray::VertexArray()
        : indexBuffer(nullptr), vertexBuffers(), vertexBufferId(0)
    {
        glGenVertexArrays(1, &this->id);
        this->Bind();
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &this->id);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(this->id);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    const Ref<IndexBuffer> &VertexArray::getIndexBuffer() const
    {
        return this->indexBuffer;
    }

    const std::vector<Ref<VertexBuffer>> &VertexArray::getVertexBuffers() const
    {
        return this->vertexBuffers;
    }

    void VertexArray::AppendVertexBuffer(const Ref<VertexBuffer> &buffer)
    {

        this->Bind();
        buffer->Bind();

        this->vertexBuffers.push_back(buffer);
        AppendLayout(buffer);
    }

    void VertexArray::ResetIndexBuffer(const Ref<IndexBuffer> &buffer)
    {
        this->Bind();
        buffer->Bind();

        this->indexBuffer = buffer;
    }

    void VertexArray::AppendLayout(const Ref<VertexBuffer> &buffer)
    {
        auto layout = buffer->getLayout();
        for (auto &element : layout)
        {
            glEnableVertexAttribArray(vertexBufferId);

            glVertexAttribPointer(vertexBufferId, 
                element.Type.Count, 
                types::gl::toEnum(element.Type.Type),
                types::gl::boolean(element.Normalized), 
                layout.getStride(),
                (GLvoid*) element.Offset);

            vertexBufferId += 1;
        }
    }
}
