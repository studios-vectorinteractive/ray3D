#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "core/input/input.h"

glm::vec3 lerp(glm::vec3 x, glm::vec3 y, float t) 
{
	return x * (1.f - t) + y * t;
}

namespace ray3D
{
	static glm::vec3 cachePosition;

	camera::camera(const cameraProps& props, const bool clampedPitch)
	{
		mPosition = props.position;
		mRotation = props.rotation;
		mFov = props.fov;
		mZFar = props.zFar;
		mZNear = props.zNear;
		mCameraSpeed = props.cameraFlySpeed;
		mCameraSensitivity = props.cameraSensitivity;
		mClampedPitch = clampedPitch;
		cachePosition = mPosition;

		reCalculateBasisVector();
		mProjectionMat = glm::perspective(mFov, props.aspectRatio, mZNear, mZFar);
	}

	auto camera::update(f32 deltaTime) -> void
	{
		if (input::isButtonPressed(mouseCode::right))
		{
			input::setCursorVisible(false);

			glm::vec2 mousePositionOffset = input::getMouseDelta() * deltaTime * mCameraSensitivity;

			glm::vec3 camRotation = mRotation;
			camRotation.x += mousePositionOffset.x;
			camRotation.y -= mousePositionOffset.y;

			if (mClampedPitch)
				camRotation.y = glm::clamp(camRotation.y, -89.0f, 89.0f);

			mRotation = camRotation;

			glm::vec3 direction;
			direction.x = cosf(glm::radians(camRotation.x)) * cosf(glm::radians(camRotation.y));
			direction.y = sinf(glm::radians(camRotation.y));
			direction.z = sinf(glm::radians(camRotation.x)) * cosf(glm::radians(camRotation.y));

			mForwardVector = glm::normalize(direction);
			mRightVector = glm::normalize(glm::cross(mForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
			mUpVector = glm::normalize(glm::cross(mRightVector, mForwardVector));


			if (input::isKeyPressed(keyCode::w)) cachePosition += mCameraSpeed * mForwardVector * deltaTime;
			if (input::isKeyPressed(keyCode::s)) cachePosition += mCameraSpeed * -mForwardVector * deltaTime;
			if (input::isKeyPressed(keyCode::a)) cachePosition += mCameraSpeed * -mRightVector * deltaTime;
			if (input::isKeyPressed(keyCode::d)) cachePosition += mCameraSpeed * mRightVector * deltaTime;
			if (input::isKeyPressed(keyCode::q)) cachePosition += mCameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f) * deltaTime;
			if (input::isKeyPressed(keyCode::e)) cachePosition += mCameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime;
		}
		else
		{
			input::setCursorVisible(true);

			glm::vec3 direction;
			direction.x = cosf(glm::radians(mRotation.x)) * cosf(glm::radians(mRotation.y));
			direction.y = sinf(glm::radians(mRotation.y));
			direction.z = sinf(glm::radians(mRotation.x)) * cosf(glm::radians(mRotation.y));

			mForwardVector = glm::normalize(direction);
			mRightVector = glm::normalize(glm::cross(mForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
			mUpVector = glm::normalize(glm::cross(mRightVector, mForwardVector));
		}

		mPosition = lerp(mPosition, cachePosition, deltaTime * 6.5f);
		//mPosition = cachePosition;
		mViewMat = glm::lookAt(mPosition, mPosition + mForwardVector, mUpVector);
	}

	auto camera::setPosition(const glm::vec3& position) -> void
	{
	}

	auto camera::setRotation(const glm::vec3& rotation) -> void
	{
	}

	auto camera::onResize(ui32 width, ui32 height) -> void
	{
		mWidth = _f32(width);
		mHeight = _f32(height);
		mProjectionMat = glm::perspective(mFov, mWidth / mHeight, mZNear, mZFar);
	}

	auto camera::reCalculateBasisVector() -> void
	{
		mForwardVector = glm::normalize(glm::vec3(0.0f) - mPosition);
		mRightVector = glm::normalize(glm::cross(mForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
		mUpVector = glm::normalize(glm::cross(mRightVector, mForwardVector));

		mViewMat = glm::lookAt(mPosition, mPosition + mForwardVector, mUpVector);
	}
}