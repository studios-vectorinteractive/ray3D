#pragma once

#include <glm/glm.hpp>
#include "core/core.h"

#define BIND_EVENT(t, x)	eventManager::addCallback<t>(std::bind(x, this, std::placeholders::_1));

namespace ray3D
{

	enum class eventType
	{
		windowCloseEvent,
		windowResizeEvent,
		mouseMovedEvent,
		mouseScrollEvent,
		keyPressedEvent,
		keyReleasedEvent,
		mouseButtonPressedEvent,
		mouseButtonReleasedEvent
	};

	class event
	{
	public:
		event() = default;
		~event() = default;

		virtual auto getEventType() -> eventType = 0;

	public:
		bool isHandled = false;
	};


	class windowCloseEvent : public event
	{
	public:
		windowCloseEvent() = default;
		virtual ~windowCloseEvent() = default;

		virtual auto getEventType() -> eventType override { return eventType::windowCloseEvent; }
	};

	class windowResizeEvent : public event
	{
	public:
		windowResizeEvent(const ui32 NewWidth, const ui32 NewHeight):mWidth(NewWidth), mHeight(NewHeight){}
		virtual ~windowResizeEvent() = default;

		virtual auto getEventType() -> eventType override { return eventType::windowResizeEvent; }

		auto getWidth() const -> ui32 { return mWidth; }
		auto getHeight() const -> ui32 { return mHeight; }

	private:
		ui32 mWidth = {};
		ui32 mHeight = {};
	};

	class mouseMovedEvent : public event
	{
	public:
		mouseMovedEvent(const f64 NewXPos, const f64 NewYPos):mXPos(_ui32(NewXPos)), mYPos(_ui32(NewYPos)) {};
		virtual ~mouseMovedEvent() = default;

		virtual auto getEventType() -> eventType override { return eventType::mouseMovedEvent; }

		auto getXPos() const -> ui32 { return mXPos; }
		auto getYPos() const -> ui32 { return mYPos; }
		auto getXYPos() const -> glm::vec<2, ui32> { return glm::vec<2, ui32>(mXPos, mYPos); }

	private:
		ui32 mXPos = {};
		ui32 mYPos = {};
	};

	class mouseScrollEvent : public event
	{
	public:
		mouseScrollEvent(const f64 XOffset, const f64 YOffset) :mXOffset(_i32(XOffset)), mYOffset(_i32(YOffset)) {};
		virtual ~mouseScrollEvent() = default;

		virtual auto getEventType() -> eventType override { return eventType::mouseScrollEvent; }

		auto getXOffset() const -> i32 { return mXOffset; }
		auto getYOffset() const -> i32 { return mYOffset; }
		auto getXYOffset() const -> glm::vec<2, i32> { return glm::vec<2, i32>(mXOffset, mYOffset); }

	private:
		i32 mXOffset = {};
		i32 mYOffset = {};
	};

	class keyPressedEvent : public event
	{
	public:
		keyPressedEvent(const i32 KeyCode, const char* KeyDebugName = nullptr):mKeyCode(KeyCode), mKeyName(KeyDebugName){}
		virtual ~keyPressedEvent() = default;

		virtual auto getEventType() -> eventType override { return eventType::keyPressedEvent; }

		auto getKeyCode() const -> i32 { return mKeyCode; }
		auto getKeyName() const -> const char* { return mKeyName; }

	private:
		i32 mKeyCode = {};
		const char* mKeyName = nullptr;
	};

	class keyReleasedEvent : public event
	{
	public:
		keyReleasedEvent(const i32 KeyCode, const char* KeyDebugName = nullptr) :mKeyCode(KeyCode), mKeyName(KeyDebugName) {}
		virtual ~keyReleasedEvent() = default;

		virtual auto getEventType() -> eventType override { return eventType::keyReleasedEvent; }

		auto getKeyCode() const -> i32 { return mKeyCode; }
		auto getKeyName() const -> const char* { return mKeyName; }

	private:
		i32 mKeyCode = {};
		const char* mKeyName = nullptr;
	};

	class mouseButtonPressedEvent : public event
	{
	public:
		mouseButtonPressedEvent(const i32 MouseButtonCode) :mMouseButtonCode(MouseButtonCode) {}
		virtual ~mouseButtonPressedEvent() = default;

		virtual auto getEventType() -> eventType override { return eventType::mouseButtonPressedEvent; }

		auto getButtonCode() const -> i32 { return mMouseButtonCode; }

	private:
		i32 mMouseButtonCode = {};
	};

	class mouseButtonReleasedEvent : public event
	{
	public:
		mouseButtonReleasedEvent(const i32 MouseButtonCode) :mMouseButtonCode(MouseButtonCode) {}
		virtual ~mouseButtonReleasedEvent() = default;

		virtual auto getEventType() -> eventType override { return eventType::mouseButtonReleasedEvent; }

	private:
		i32 mMouseButtonCode = {};
	};

	template<class t_event>
	inline auto getEventFromBase(const event& incEvent) -> const t_event&
	{
		//TODO: additional safety checks required
		return static_cast<const t_event&>(incEvent);
	}
}