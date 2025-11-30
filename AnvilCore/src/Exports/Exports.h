#pragma once
#include "../Logger/Sinks.h"
#include "../Core.h"

ANVIL_EXPORT void InitCoreLogger(uint32_t sinksAvailable, LogCallbackFn cb);
ANVIL_EXPORT void ToggleSinkLogs(uint32_t sinks);

ANVIL_EXPORT void StartGameLoop();

ANVIL_EXPORT void StopGameLoop();
ANVIL_EXPORT void QuitSDL();