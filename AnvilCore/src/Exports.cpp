#include "pch.h"
#include "Exports.h"
#include "Logger/Logger.h"

#include <SDL3/SDL.h>

// TODO: make a class/struct for these
static SDL_GPUDevice* g_Device = nullptr;
static SDL_Window* g_Window = nullptr;
static std::thread g_GameLoopThread;
static std::atomic<bool> g_Running = false;

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
		LOG_ERROR("SDL_init failed!");
		return;
	}
	LOG_INFO("SDL initialized");

	if (!(g_Device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_DXIL, false, nullptr)))
	{
		LOG_ERROR("Failed to create GPU device!");
		return;
	}
	LOG_INFO("GPU device created");

	SDL_PropertiesID props = SDL_CreateProperties();
	SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, hwnd);
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, static_cast<Sint64>(width));
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, static_cast<Sint64>(height));

	if (!(g_Window = SDL_CreateWindowWithProperties(props)))
	{
		LOG_ERROR("Failed to create SDL window!");
		return;
	}
	LOG_INFO("SDL window created");

	if (!SDL_ClaimWindowForGPUDevice(g_Device, g_Window))
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
	if (g_Running)
		return;

	g_Running = true;
	g_GameLoopThread = std::thread([] 
		{
			LOG_INFO("Starting game loop");

			while (g_Running)
				Iterate();

			LOG_INFO("Stopping game loop");
		});
}

void StopGameLoop()
{
	if (!g_Running)
		return;

	g_Running = false;


	if (g_GameLoopThread.joinable())
		g_GameLoopThread.join();
}

void Iterate()
{
	if (!Tick())
		g_Running = false;
}

bool Tick()
{
	LOG_TRACE("Tick");
	Update();

	if (!Render())
		return false;

	return true;
}

void Update()
{
	// updates go here
}

bool Render()
{
	SDL_GPUCommandBuffer* cmdbuf = SDL_AcquireGPUCommandBuffer(g_Device);
	if (!cmdbuf)
	{
		LOG_ERROR("AcquireGPUCommandBuffer failed: {}", SDL_GetError());
		return false;
	}

	SDL_GPUTexture* swapchainTexture;
	if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdbuf, g_Window, &swapchainTexture, nullptr, nullptr))
	{
		LOG_ERROR("WaitAndAcquireGPUSwapchainTexture failed: {}", SDL_GetError());
		return false;
	}

	if (swapchainTexture)
	{
		SDL_GPUColorTargetInfo colorTargetInfo =
		{
			.texture = swapchainTexture,
			.clear_color = { 1.0f, 0.0f, 0.0f, 1.0f },
			.load_op = SDL_GPU_LOADOP_CLEAR,
			.store_op = SDL_GPU_STOREOP_STORE
		};

		SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmdbuf, &colorTargetInfo, 1, nullptr);
		SDL_EndGPURenderPass(renderPass);
	}

	SDL_SubmitGPUCommandBuffer(cmdbuf);

	return true;
}

void QuitSDL()
{
	SDL_DestroyWindow(g_Window);
	SDL_DestroyGPUDevice(g_Device);
	SDL_Quit();
}
