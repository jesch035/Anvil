#include "Exports.h"

void InitEngineCore(LogCallbackFn callback)
{
	Logger<EditorSink>::Get().Init("Core", callback);
}

void TestLoggingFunction()
{
	LOG_EDITOR_INFO("Colbertson");
}