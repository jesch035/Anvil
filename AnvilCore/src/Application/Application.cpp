#include "../pch.h"
#include "Application.h"
#include "../Logger/Logger.h"

void Application::Iterate()
{
	if (!Tick())
		m_Running = false;
}

void Application::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)

	}
}

bool Application::Tick()
{
	Update();

	if (!Render())
		return false;

	return true;
}

void Application::Update()
{
	// updates go here
}

bool Application::Render()
{
	SDL_GPUCommandBuffer* cmdbuf = SDL_AcquireGPUCommandBuffer(m_Device);
	if (!cmdbuf)
	{
		LOG_ERROR("AcquireGPUCommandBuffer failed: {}", SDL_GetError());
		return false;
	}

	SDL_GPUTexture* swapchainTexture;
	if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdbuf, m_Window, &swapchainTexture, nullptr, nullptr))
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
