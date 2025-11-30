#pragma once
#include <SDL3/SDL.h>
#include <thread>

#include "../Logger/Logger.h"
#include "../Events/Event.h"

class Application
{
public:
	static Application& Get()
	{
		static Application instance;
		return instance;
	}

	bool SetGPUDevice(SDL_GPUDevice* device) { return m_Device = device; }
	SDL_GPUDevice* GetGPUDevice() const { return m_Device; }

	bool SetWindow(SDL_Window* window) { return m_Window = window; }
	SDL_Window* GetWindow() const { return m_Window; }

	void StartGameLoopThread(std::thread thread) { m_GameLoopThread = std::move(thread); }

	bool IsRunning() const { return m_Running; }

	template<std::invocable F>
	void Start(F&& func)
	{
		m_Running = true; 
		m_GameLoopThread = std::thread(std::forward<F>(func));
	}

	void Stop()
	{
		m_Running = false;

		LOG_INFO("Stopping game loop");

		if (m_GameLoopThread.joinable())
			m_GameLoopThread.join();
	}

	void Iterate();

	void PollEvents();

	bool Tick();
		void Update();
		bool Render();
private:
	Application() = default;
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	SDL_GPUDevice* m_Device = nullptr;
	SDL_Window* m_Window = nullptr;
	std::thread m_GameLoopThread;
	std::atomic<bool> m_Running = false;
	EventBus bus;
	EventQueue queue;
};