#pragma once

#include <spdlog/spdlog.h>

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

#ifdef BA_DIST
#define BA_LOG_TRACE(...)
#define BA_LOG_DEBUG(...)
#else
#define BA_LOG_TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__)
#define BA_LOG_DEBUG(...) ::Log::GetLogger()->debug(__VA_ARGS__)
#endif

#define BA_LOG_INFO(...) ::Log::GetLogger()->info(__VA_ARGS__)
#define BA_LOG_WARN(...) ::Log::GetLogger()->warn(__VA_ARGS__)
#define BA_LOG_ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__)
#define BA_LOG_FATAL(...) ::Log::GetLogger()->critical(__VA_ARGS__)
