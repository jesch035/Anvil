#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <queue>
#include <variant>
#include <functional>

struct Event1
{
	int x;
};

struct Event2
{
	int x, y;
};

struct Event3
{
	int x, y, z;
};

using Event = std::variant<Event1, Event2, Event3>;
using ListenerFn = std::function<void(const Event&)>;

class EventBus
{
public:
	template<typename T>
	void Subscribe(std::function<void(const T& e)> func)
	{
		auto wrapper = [func](const Event& e)
			{
				func(std::get<T>(e));
			};

		m_Listeners[variant_index<T>()].push_back(wrapper);
	}

	void Dispatch(const Event& e)
	{
		auto idx = e.index();
		for (auto& fn : m_Listeners[idx])
			fn(e);
	}

private:
	template<typename T>
	static constexpr std::size_t variant_index() {
		return detail_variant_index<T, Event>();
	}

	// Helper to compute type index at compile-time
	template<typename T, typename Variant, std::size_t I = 0>
	static consteval std::size_t detail_variant_index() {
		if constexpr (I == std::variant_size_v<Variant>) {
			static_assert(I != I, "Type not in variant");
			return 0;
		}
		else if constexpr (std::is_same_v<T, std::variant_alternative_t<I, Variant>>) {
			return I;
		}
		else {
			return detail_variant_index<T, Variant, I + 1>();
		}
	}

	std::array<std::vector<ListenerFn>, std::variant_size_v<Event>> m_Listeners;
};

class EventQueue {
public:
	template<typename T>
	void Push(const T& e) {
		m_Events.push(Event(e));
	}

	void Process(EventBus& bus) {
		while (!m_Events.empty())
		{
			bus.Dispatch(m_Events.front());
			m_Events.pop();
		}
	}

private:
	std::queue<Event> m_Events;
};