#include "pch.h"
#include "Exports.h"
#include "Logger/Logger.h"
#include "Application/Application.h"

#include <SDL3/SDL.h>

static Application& s_App = Application::Get();

void InitCoreLogger(uint32_t sinksAvailable, LogCallbackFn callback)
{
	std::vector<spdlog::sink_ptr> sinks;
	sinks.reserve(4);

	if (sinksAvailable & static_cast<uint32_t>(SinkFlags::CallbackSink))
		sinks.push_back(std::make_shared<CallbackSink>(callback));

	Logger::Init("Core", std::move(sinks), sinksAvailable);
}

// ONLY TO BE USED IN EDITOR
#ifdef _WIN32
ANVIL_EXPORT void InitEditorSDL(HWND hwnd, int width, int height)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		LOG_ERROR("SDL_init failed!");
		return;
	}
	LOG_INFO("SDL initialized");

	if (!s_App.SetGPUDevice(SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_DXIL, false, nullptr)))
	{
		LOG_ERROR("Failed to create GPU device!");
		return;
	}
	LOG_INFO("GPU device created");

	SDL_PropertiesID props = SDL_CreateProperties();
	SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, hwnd);
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, static_cast<Sint64>(width));
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, static_cast<Sint64>(height));

	if (!s_App.SetWindow(SDL_CreateWindowWithProperties(props)))
	{
		LOG_ERROR("Failed to create SDL window!");
		return;
	}
	LOG_INFO("SDL window created");

	if (!SDL_ClaimWindowForGPUDevice(s_App.GetGPUDevice(), s_App.GetWindow()))
	{
		LOG_ERROR("GPUClaimWindow failed!");
		return;
	}
	LOG_INFO("Claimed window for GPU device");
}
#endif

void ToggleSinkLogs(uint32_t sinks)
{
	Logger::ToggleSinkLogs(sinks);
}

void StartGameLoop()
{
	if (s_App.IsRunning())
		return;

	s_App.Start([]
		{
			LOG_INFO("Starting game loop");

			while (s_App.IsRunning())
				s_App.Iterate();

			LOG_INFO("Stopping game loop");
		});
}

void StopGameLoop()
{
	if (!s_App.IsRunning())
		return;

	s_App.Stop();
}

void QuitSDL()
{
	SDL_DestroyWindow(s_App.GetWindow());
	SDL_DestroyGPUDevice(s_App.GetGPUDevice());
	SDL_Quit();
}
