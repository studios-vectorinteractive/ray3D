#pragma once
#include <queue>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

#include "event.h"
#include "core/core.h"

namespace ray3D
{
	using eventCallbackFn = std::function<void(event*)>;

	class eventManager
	{
	public:
		static auto init() -> void;
		static auto shutdown() -> void;

		static auto dispatchEvents() -> void;
		template<eventType t_event>
		static auto addCallback(eventCallbackFn callback)
		{
			mInvocationList[t_event].emplace_back(callback);
		}

		static auto pushEvent(std::shared_ptr<event> IncEvent) -> void;

		//deleted functions
		eventManager() = delete;
		eventManager(const eventManager&) = delete;
		eventManager& operator=(const eventManager&) = delete;

	private:
		static inline std::queue<std::shared_ptr<event>> mEventQueue = {};
		static inline std::unordered_map<eventType, std::vector<eventCallbackFn>> mInvocationList = {};
		static inline bool mInitialized = false;
	};
}