#pragma once
#include <spdlog/sinks/base_sink.h>
#include "Logger.h"

enum class SinkFlags : uint32_t
{
	None = 0,
	CallbackSink = 1 << 0,
};

typedef void(*LogCallbackFn)(const char* message);

class CallbackSink : public spdlog::sinks::base_sink<std::mutex>
{
public:
	CallbackSink(LogCallbackFn fn) : m_CallbackFn(fn) {}

private:
	void sink_it_(const spdlog::details::log_msg& msg) override;

	void flush_() override {}

	LogCallbackFn m_CallbackFn = nullptr;
};