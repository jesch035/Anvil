#pragma once
#include <cstdint>
#include <vector>
#include <array>

template<typename T>
struct EventID
{
	static const uint32_t value;
};

template<typename T>
const uint32_t EventID<T>::value = []()
	{
		static uint32_t counter = 0;
		return counter++;
	};

constexpr uint32_t MAX_EVENT_TYPES = 256;

class EventBus
{
public:
	using ListenerFn = void(*)(const void*);

	template<typename EventType>
	void Subscribe(void(*func)(const EventType&))
	{
		auto wrapper = +[](const void* e)
			{
				func(*static_cast<const EventType*>(e));
			};

		m_Listeners[EventID<EventType>::value].push_back(wrapper);
	}

	template<typename EventType>
	void Emit(const EventType& event) const
	{
		uint32_t id = EventID<EventType>::value;
		for (auto& function : listeners[id])
			fn(&event);
	}

private:
	std::array<std::vector<ListenerFn>, MAX_EVENT_TYPES> m_Listeners;
};