#pragma once
#include <spdlog/sinks/base_sink.h>

typedef void(*LogCallbackFn)(const char* message);

class EditorSink : public spdlog::sinks::base_sink<std::mutex>
{
public:
	EditorSink(LogCallbackFn fn) : m_CallbackFn(fn) {}

private:
	void sink_it_(const spdlog::details::log_msg& msg) override;

	void flush_() override {}

	LogCallbackFn m_CallbackFn = nullptr;

	void SendMessageToEditor(const std::string& msg);
};