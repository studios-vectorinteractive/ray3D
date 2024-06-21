#include "buffer.h"
#include <glad/glad.h>

namespace ray3D
{
    vertexBuffer::vertexBuffer(std::vector<f32>& vertBuffer, const vertAttribLayoutType attribLayoutType):
        mAttribLayout(vertAttribsLayout::getLayout(attribLayoutType))
    {
        mVertices = std::move(vertBuffer);
        auto data = mVertices.data();
        ui32 stride = mAttribLayout.getStride();

        glGenBuffers(1, &mVertBufferID);
        glGenVertexArrays(1, &mVertAttribArrayID);

        glBindVertexArray(mVertAttribArrayID);
        glBindBuffer(GL_ARRAY_BUFFER, mVertBufferID);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(f32), mVertices.data(), GL_STATIC_DRAW);

        i32 idx = 0;
        for(const vertAttribElement& element : mAttribLayout.getElements())
        {
            glVertexAttribPointer(idx, element.getElementCount(), getGLShaderDataType(element.shaderType), element.normalized, stride, (void*)(element.offset));
            glEnableVertexAttribArray(idx++);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    vertexBuffer::~vertexBuffer()
    {
        glDeleteBuffers(1, &mVertBufferID);
        glDeleteVertexArrays(1, &mVertAttribArrayID);
    }

    auto vertexBuffer::bind() -> void 
    {
        glBindVertexArray(mVertAttribArrayID);
    }

    indexBuffer::indexBuffer(std::vector<ui32>& indexBuffer)
    {
        mIndices = indexBuffer;
        mIndexCount = mIndices.size();

        glGenBuffers(1, &mIndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ui32) * mIndices.size(), mIndices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    indexBuffer::~indexBuffer()
    {
        glDeleteBuffers(1, &mIndexBufferID);
    }

    auto indexBuffer::bind() -> void 
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
    }
}
