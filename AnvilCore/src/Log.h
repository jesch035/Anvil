#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <mutex>

typedef void(*LogCallbackFn)(const char* message);

class WinFormsSink : public spdlog::sinks::base_sink<std::mutex>
{
protected:
	void sink_it_(const spdlog::details::log_msg& msg) override;

	void flush_() override {}
};

class Logger
{
public:
	static Logger& Get()
	{
		static Logger logger;
		return logger;
	}

	std::shared_ptr<WinFormsSink> m_WinFormsSink = nullptr;
	std::shared_ptr<spdlog::logger> m_WinFormsLogger = nullptr;

	LogCallbackFn m_CallbackFn = nullptr;

private:
	Logger() {}
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
};

#define LOG_EDITOR_INFO(...) Logger::Get().m_WinFormsLogger->info(__VA_ARGS__)
