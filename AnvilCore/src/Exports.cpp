#include "Exports.h"
#include "Log.h"
#include <memory>

void InitEngineCore(LogCallbackFn callback)
{
	Logger::Init("Core", { std::make_shared<EditorSink>(callback) });
}

void TestLoggingFunction()
{
	uint8_t x = 5;
	uint8_t y = 6;
	LOG_TRACE("Numbers: {}, {}", x, y);
}