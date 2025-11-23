#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <mutex>

#include "Sinks.h"

enum class LogLevel
{
	Trace,
	Info,
	Warn,
	Error
};

template<typename T>
class Logger
{
public:
	static Logger<T>& Get()
	{
		static Logger<T> logger;
		return logger;
	}

	template<typename... Args>
	void Init(Args&&... args)
	{
		m_Sink = std::make_shared<T>(std::forward<Args>(args)...);
		m_Logger = std::make_shared<spdlog::logger>("Default", m_Sink);
	}

	template<typename S = std::string, typename... Args>
	void Init(const S& name, Args&&... args)
	{
		m_Sink = std::make_shared<T>(std::forward<Args>(args)...);
		m_Logger = std::make_shared<spdlog::logger>(name, m_Sink);
	}

	template<typename... Args>
	void Log(LogLevel level, fmt::format_string<Args...> fmt, Args&&... args)
	{
		switch (level)
		{
		case LogLevel::Trace: m_Logger->trace(fmt, std::forward<Args>(args)...); break;
		case LogLevel::Info: m_Logger->info(fmt, std::forward<Args>(args)...); break;
		case LogLevel::Warn: m_Logger->warn(fmt, std::forward<Args>(args)...); break;
		case LogLevel::Error: m_Logger->error(fmt, std::forward<Args>(args)...); break;
		}
	}
private:
	std::shared_ptr<T> m_Sink = nullptr;
	std::shared_ptr<spdlog::logger> m_Logger = nullptr;

	LogCallbackFn m_CallbackFn = nullptr;

	Logger() {}
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
};

#define LOG_EDITOR_INFO(...) Logger<EditorSink>::Get().Log(LogLevel::Info, __VA_ARGS__)
