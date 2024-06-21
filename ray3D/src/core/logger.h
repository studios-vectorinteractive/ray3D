#pragma once

#include <spdlog/spdlog.h>

namespace ray3D
{
	class logger
	{
	public:

		static auto init() -> void;
		static auto shutdown() -> void;

		static auto getLogger() -> std::shared_ptr<spdlog::logger>& { return mLogger; }

		//deleted functions
		logger() = delete;
		logger(const logger&) = delete;
		logger& operator=(const logger&) = delete;

	private:
		static inline bool mInitialized = false;
		static inline std::shared_ptr<spdlog::logger> mLogger = {};
	};

	inline void report_assertion_failure(const char* expression, const char* message, const char* file, int line)
	{
		logger::getLogger()->critical("{} Failed : Message - {} in file : {} at {}", expression, message, file, line);
	}
}

#ifdef _DEBUG
#define R3D_LOGD(...) ::ray3D::logger::getLogger()->debug(__VA_ARGS__);
#define R3D_LOGI(...) ::ray3D::logger::getLogger()->info(__VA_ARGS__);
#define R3D_LOGW(...) ::ray3D::logger::getLogger()->warn(__VA_ARGS__);
#define R3D_LOGE(...) ::ray3D::logger::getLogger()->error(__VA_ARGS__);
#define R3D_LOGT(...) ::ray3D::logger::getLogger()->trace(__VA_ARGS__);
#else
#define R3D_LOGD(...) 
#define R3D_LOGI(...) 
#define R3D_LOGW(...) 
#define R3D_LOGE(...) 
#define R3D_LOGT(...) 
#endif // _DEBUG

