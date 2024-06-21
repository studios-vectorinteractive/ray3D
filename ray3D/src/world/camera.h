#pragma once
#include "core/core.h"
#include <glm/glm.hpp>

namespace ray3D
{
	typedef struct cameraProps
	{
		glm::vec3 position;
		glm::vec3 rotation;		//euler
		f32 fov;
		f32 aspectRatio;
		f32 zNear;
		f32 zFar;
		f32 cameraFlySpeed;
		f32 cameraSensitivity;
	}cameraProps;

	class camera
	{
	public:
		camera(const cameraProps& props, const bool clampedPitch = true);
		~camera() = default;

		auto update(f32 deltaTime) -> void;
		
		auto setPosition(const glm::vec3& position) -> void;
		auto setRotation(const glm::vec3& rotation) -> void;

		auto onResize(ui32 width, ui32 height) -> void;

		auto getPosition() const -> const glm::vec3& { return mPosition; }
		auto getPosition() -> glm::vec3& { return mPosition; }
		auto getUpVector() const -> const glm::vec3& { return mUpVector; }
		auto getRightVector() const -> const glm::vec3& { return mRightVector; }
		auto getForwardVector() const -> const glm::vec3& { return mForwardVector; }
		auto getProjectionMat() -> glm::mat4& { return mProjectionMat; }
		auto getViewMat() -> glm::mat4& { return mViewMat; }

	private:
		auto reCalculateBasisVector() -> void;

	private:

		//TODO: when ECS inplace, position and rotation will be the part of transform component
		glm::vec3 mPosition = {};
		glm::vec3 mRotation = {}; //Euler

		glm::vec3 mUpVector = {};
		glm::vec3 mRightVector = {};
		glm::vec3 mForwardVector = {};

		glm::mat4 mProjectionMat = {};
		glm::mat4 mViewMat = {};

		f32 mZNear;
		f32 mZFar;
		f32 mFov = {};
		f32 mWidth = {};
		f32 mHeight = {};

		f32 mCameraSpeed = 5.0f;
		f32 mCameraSensitivity = 5.0f;

		bool mClampedPitch = true;
	};
}