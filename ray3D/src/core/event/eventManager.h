#pragma once
#include <queue>
#include <vector>
#include <memory>
#include <utility>
#include <functional>
#include <unordered_map>

#include "event.h"
#include "core/core.h"

namespace ray3D
{
	using eventCallbackFn = std::function<void(event&)>;

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

		template<class t_event, class... t_args>
		static auto pushEvent(t_args... args) -> void
		{
			mEventQueue.emplace(std::make_unique<t_event>(std::forward<t_args>(args)...));
		}

	private:
		static inline std::queue<std::unique_ptr<event>> mEventQueue = {};
		static inline std::unordered_map<eventType, std::vector<eventCallbackFn>> mInvocationList = {};
		static inline bool mInitialized = false;
	};
}