#include "Exports.h"
#include "Log.h"
#include <memory>

void InitEngineCore(uint32_t sinkFlags, LogCallbackFn callback)
{
	std::vector<spdlog::sink_ptr> sinks;
	sinks.reserve(4);

	if (sinkFlags & static_cast<uint32_t>(SinkFlags::CallbackSink))
		sinks.push_back(std::make_shared<CallbackSink>(callback));

	Logger::Init("Core", std::move(sinks));
}

void TestLoggingFunction()
{
	uint8_t x = 5;
	uint8_t y = 6;
	LOG_TRACE("Numbers: {}, {}", x, y);
}