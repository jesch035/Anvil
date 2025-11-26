#pragma once
#include "Logger/Sinks.h"
#include "Core.h"

ANVIL_EXPORT void InitEngineCore(uint32_t sinksAvailable, LogCallbackFn cb);
ANVIL_EXPORT void TestLoggingFunction();
ANVIL_EXPORT void ToggleSinkLogs(uint32_t sinks);