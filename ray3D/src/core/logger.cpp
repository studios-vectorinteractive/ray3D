#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace ray3D
{
	auto logger::init() -> void
	{
		if (mInitialized)
		{
			mLogger->info("Logger initialized already");
			return;
		}

		spdlog::set_pattern("[%Y-%m][%I:%M:%S %p] %^[%l]\t:\t%v%$");

		std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> colorMtSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		colorMtSink->set_pattern("[%Y-%m][%I:%M:%S %p] %^[%l]\t:\t%v%$");
		mLogger = std::make_shared<spdlog::logger>("Ray3D logger", colorMtSink);
		mLogger->set_level(spdlog::level::trace);
		mLogger->flush_on(spdlog::level::trace);
		spdlog::register_logger(mLogger);

		mLogger->info("Logging initalized");

		mInitialized = true;
	}

	auto logger::shutdown() -> void
	{
		mLogger->info("Shutting down the logger");
		spdlog::shutdown();
		mLogger.reset();
		mInitialized = false;
	}
}