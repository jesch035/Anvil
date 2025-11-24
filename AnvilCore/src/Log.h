#pragma once
#include <spdlog/spdlog.h>
#include <vector>
#include <cassert>

enum class LogLevel
{
	Trace,
	Info,
	Warn,
	Error
};

class Logger
{
public:
	static void Init(const std::string& name, std::vector<spdlog::sink_ptr>&& sinks)
	{
		assert(!m_Logger && "Assertion: Log already initialized");
		if (m_Logger)
			return;

		m_Sinks = std::move(sinks);
		if (m_Logger = std::make_shared<spdlog::logger>(name, m_Sinks.begin(), m_Sinks.end()))
			m_Logger->set_level(spdlog::level::trace);
	}

	template<typename... Args>
	static void Log(LogLevel level, fmt::format_string<Args...> fmt, Args&&... args)
	{
		assert(m_Logger && "Assertion: Log not initialized");
		if (m_Logger)
		{
			switch (level)
			{
			case LogLevel::Trace: m_Logger->trace(fmt, std::forward<Args>(args)...); break;
			case LogLevel::Info: m_Logger->info(fmt, std::forward<Args>(args)...); break;
			case LogLevel::Warn: m_Logger->warn(fmt, std::forward<Args>(args)...); break;
			case LogLevel::Error: m_Logger->error(fmt, std::forward<Args>(args)...); break;
			}
		}
	}
private:
	Logger() = delete;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	static inline std::vector<spdlog::sink_ptr> m_Sinks;
	static inline std::shared_ptr<spdlog::logger> m_Logger;
};

#define LOG_TRACE(...) Logger::Log(LogLevel::Trace, __VA_ARGS__)
#define LOG_INFO(...) Logger::Log(LogLevel::Info, __VA_ARGS__)
#define LOG_WARN(...) Logger::Log(LogLevel::Warn, __VA_ARGS__)
#define LOG_ERROR(...) Logger::Log(LogLevel::Error, __VA_ARGS__)
