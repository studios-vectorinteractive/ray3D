#include "texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace ray3D
{
	texture::texture(const std::string& path, const textureType texType, const ui32 mip)
	{
		i32 width = 0;
		i32 height = 0;
		i32 channels = 0;

		stbi_uc* imgData = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (!imgData)
		{
			R3D_LOGE("Failed to create texture : {}", path);
			return;
		}

		mWidth = _ui32(width);
		mHeight = _ui32(height);
		mChannels = _ui32(channels);

		mTexType = mChannels > 3 ? textureType::_rgba : textureType::_rgb;

		createTexture(mip, width, height, imgData);

		R3D_LOGD("Loaded texture successfully : {}", path);
	}

	texture::texture(const ui32 width, const ui32 height, const textureType texType, const ui32 mip)
	{
		mWidth = _ui32(width);
		mHeight = _ui32(height);

		switch (mTexType)
		{
		case textureType::_rgba:
			mChannels = 4;
			break;
		case textureType::_rgb:
			mChannels = 3;
			break;
		case textureType::_r:
			mChannels = 1;
			break;
		}

		createTexture(mip, width, height, nullptr);

		R3D_LOGD("Color attachment created successfully!");
	}

	auto texture::createTexture(const ui32 mip, i32 width, i32 height, unsigned char* imgData) -> void
	{
		GLint internalFormat = GL_NONE;
		GLint format = GL_NONE;

		switch (mTexType)
		{
		case textureType::_rgba:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			break;
		case textureType::_rgb:
			internalFormat = GL_RGB8;
			format = GL_RGB;
			break;
		case textureType::_r:
			internalFormat = GL_R32F;
			format = GL_R;
			break;
		}

		glGenTextures(1, &mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		glTexImage2D(GL_TEXTURE_2D, mip, internalFormat, (GLsizei)width, (GLsizei)height, 0, format, GL_UNSIGNED_BYTE, imgData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			//TODO : Make it configurable
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);			//TODO : Make it configurable
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		//TODO : Make it configurable
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		//TODO : Make it configurable

		if (mip)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
			mMipLevel = mip;
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	texture::~texture()
	{
		glDeleteTextures(1, &mTextureID);
	}

	auto texture::bind() -> void
	{
		glBindTexture(GL_TEXTURE_2D, mTextureID);
	}

	auto texture::create(const std::string& path, const textureType texType, const ui32 mip) -> std::unique_ptr<texture>
	{
		return std::make_unique<texture>(path, texType, mip);
	}

	auto texture::create(const ui32 width, const ui32 height, const textureType texType, const ui32 mip) -> std::unique_ptr<texture>
	{
		return std::make_unique<texture>(width, height, texType, mip);
	}
}