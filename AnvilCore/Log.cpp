#include "Log.h"

static LogCallback g_callback = nullptr;

extern "C" __declspec(dllexport) void SetLogCallback(LogCallback cb)
{
	g_callback = cb;

	auto sink = std::make_shared<CallbackSink>();
	auto logger = std::make_shared<spdlog::logger>("CoreLogger", sink);

	spdlog::set_default_logger(logger);
	spdlog::flush_on(spdlog::level::info);
}

extern "C" void TestLoggingFunction()
{
	spdlog::info("Message from dll!");
}

void ForwardLog(const std::string& msg)
{
	if (g_callback)
		g_callback(msg.c_str());
}