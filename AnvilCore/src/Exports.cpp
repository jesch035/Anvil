#include "pch.h"
#include "Exports.h"
#include "Logger/Logger.h"

#include <SDL3/SDL.h>

static SDL_GPUDevice* g_Device = nullptr;

void InitCoreLogger(uint32_t sinksAvailable, LogCallbackFn callback)
{
	std::vector<spdlog::sink_ptr> sinks;
	sinks.reserve(4);

	if (sinksAvailable & static_cast<uint32_t>(SinkFlags::CallbackSink))
		sinks.push_back(std::make_shared<CallbackSink>(callback));

	Logger::Init("Core", std::move(sinks), sinksAvailable);
}

#ifdef _WIN32
ANVIL_EXPORT void InitEditorSDL(HWND hwnd, int width, int height)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		LOG_ERROR("SDL init failed!");
		return;
	}
	LOG_INFO("SDL initialized");


	if (!(g_Device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_DXIL, false, nullptr)))
	{
		LOG_ERROR("Failed to create GPU device!");
		return;
	}
	LOG_INFO("GPU device created");

	// TODO: Get clear color to render to winforms panel

}
#endif

void ToggleSinkLogs(uint32_t sinks)
{
	Logger::ToggleSinkLogs(sinks);
}

void QuitSDL()
{
	SDL_DestroyGPUDevice(g_Device);
}
