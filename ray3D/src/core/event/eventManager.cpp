#include "eventManager.h"
#include "core/logger.h"

namespace ray3D
{
	auto eventManager::init() -> void
	{
		if (mInitialized)
		{
			R3D_LOGD("Event System already initialized");
			return;
		}

		//TODO: maybe some system initialization code here

		R3D_LOGD("Event System initialized");
		mInitialized = true;
	}

	auto eventManager::shutdown() -> void
	{
		if (!mEventQueue.empty())
		{
			dispatchEvents();
		}

		mInvocationList.clear();

		R3D_LOGD("Event System shutting down");
		mInitialized = false;
	}

	auto eventManager::dispatchEvents() -> void
	{
		if (mEventQueue.empty())
		{
			return;
		}

		while (!mEventQueue.empty())
		{
			std::unique_ptr<event>& incEvent = mEventQueue.front();
			eventType incEventType = incEvent->getEventType();

			if (mInvocationList.find(incEventType) != mInvocationList.end())
			{
				for (eventCallbackFn& callbacks : mInvocationList[incEventType])
				{
					callbacks(*incEvent);
					incEvent->isHandled = true;
				}
			}

			mEventQueue.pop();
		}
	}
}