#include "Exports.h"
#include "Logger/Logger.h"
#include <memory>

void InitEngineCore(uint32_t sinksAvailable, LogCallbackFn callback)
{
	std::vector<spdlog::sink_ptr> sinks;
	sinks.reserve(4);

	if (sinksAvailable & static_cast<uint32_t>(SinkFlags::CallbackSink))
		sinks.push_back(std::make_shared<CallbackSink>(callback));

	Logger::Init("Core", std::move(sinks), sinksAvailable);
}

void TestLoggingFunction()
{
	uint8_t x = 5;
	uint8_t y = 6;
	LOG_TRACE("Numbers: {}, {}", x, y);
}

void ToggleSinkLogs(uint32_t sinks)
{
	Logger::ToggleSinkLogs(sinks);
}