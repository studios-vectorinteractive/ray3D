#pragma once
#include "core/core.h"

#include <string>
#include <memory>

namespace ray3D
{
	enum class textureType
	{
		_rgba,
		_rgb,
		_r
	};

	class texture
	{
	public:

		texture(const std::string& path, const textureType texType = textureType::_rgb, const ui32 mip = 0);
		texture(const ui32 width, const ui32 height, const textureType texType = textureType::_rgb, const ui32 mip = 0);
		
		~texture();

		auto bind() -> void;

		auto getWidth() const -> ui32 { return mWidth; }
		auto getHeight() const -> ui32 { return mHeight; }
		auto getChannels() const -> ui32 { return mChannels; }
		auto getMipLevels() const -> ui32 { return mMipLevel; }
		auto getTextureID() const -> ui32 { return mTextureID; }

		static auto create(const std::string& path, const textureType texType = textureType::_rgb, const ui32 mip = 0) -> std::unique_ptr<texture>;
		static auto create(const ui32 width, const ui32 height, const textureType texType = textureType::_rgb, const ui32 mip = 0) -> std::unique_ptr<texture>;

	private:
		auto createTexture(const ui32 mip, i32 width, i32 height, unsigned char* imgData) -> void;

	private:
		ui32 mWidth = {};
		ui32 mHeight = {};
		ui32 mChannels = {};
		ui32 mTextureID = {};
		ui32 mMipLevel = {};
		textureType mTexType = {};
	};
}