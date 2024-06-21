#include "framebuffer.h"

#include <string>
#include <vector>

#include <glad/glad.h>

#include "buffer.h"
#include "vertAttribs.h"
#include "texture.h"

namespace ray3D
{

	const std::string quadVert = R"(
	
		

	)";

	static std::vector<posColVert> quadVertices =
	{
		{{-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
		{{ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 0.0f}},
		{{ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 0.0f}},
		{{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}}
	};

	static std::vector<ui32> quadIndices =
	{
		0, 1, 3,
		1, 2, 3
	};

	frameBuffer::frameBuffer(const ui32 width, const ui32 height):mWidth(width), mHeight(height)
	{
		mQuadVertBuffer = vertexBuffer::create(quadVertices, vertAttribLayoutType::pos_col);
		mQuadIndexBuffer = indexBuffer::create(quadIndices);

		reCreateFramebuffer(false);
	}

	frameBuffer::~frameBuffer()
	{
		glDeleteFramebuffers(1, &mFramebufferID);
	}

	auto frameBuffer::bind() -> void
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferID);
	}

	auto frameBuffer::unBind() -> void
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	auto frameBuffer::draw() -> void
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mQuadVertBuffer->bind();
		mQuadIndexBuffer->bind();

		glDrawElements(GL_TRIANGLES, mQuadIndexBuffer->getCount(), GL_UNSIGNED_INT, 0);
	}

	auto frameBuffer::onResize(const ui32 newWidth, const ui32 newHeight)
	{
		mWidth = newWidth;
		mHeight = newHeight;
		reCreateFramebuffer(true);
	}

	auto frameBuffer::create(const ui32 width, const ui32 height) ->std::unique_ptr<frameBuffer>
	{
		return std::make_unique<frameBuffer>(width, height);
	}

	auto frameBuffer::reCreateFramebuffer(bool invalidate) -> void
	{
		//Delete previous fbo
		if(invalidate)
		{
			mDepthStencilAttachment.reset(nullptr);
			mColorAttachment.reset(nullptr);
			glDeleteFramebuffers(1, &mFramebufferID);
		}

		glGenFramebuffers(1, &mFramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferID);

		mColorAttachment = texture::create(mWidth, mHeight, textureType::_rgba);
		mDepthStencilAttachment = texture::create(mWidth, mHeight, textureType::_r);

		mColorAttachment->bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorAttachment->getTextureID(), mColorAttachment->getMipLevels());

		mDepthStencilAttachment->bind();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH24_STENCIL8, GL_TEXTURE_2D, mDepthStencilAttachment->getTextureID());
	}
}