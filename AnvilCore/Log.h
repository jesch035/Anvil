#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <mutex>

extern "C" {
	typedef void(*LogCallback)(const char* message);

	__declspec(dllexport) void SetLogCallback(LogCallback cb);
	__declspec(dllexport) void TestLoggingFunction();
}

void ForwardLog(const std::string& msg);

class CallbackSink : public spdlog::sinks::base_sink<std::mutex>
{
protected:
	void sink_it_(const spdlog::details::log_msg& msg) override
	{
		spdlog::memory_buf_t buffer;
		formatter_->format(msg, buffer);
		ForwardLog(fmt::to_string(buffer));
	}

	void flush_() override {}
};