#pragma once
#include <vector>
#include <queue>
#include <variant>
#include <tuple>
#include <memory>

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

template<typename T>
struct Callback
{
	void (*fn)(void*, const T&);						// callback function
	std::unique_ptr<void, void(*)(void*)> userdata;     // object/lambda/etc
};

class EventBus
{
public:
	template<typename T, typename Callable>
	void Subscribe(Callable&& cb)
	{
		using Decayed = std::decay_t<Callable>;

		auto* rawPtr = new Decayed(std::forward<Callable>(cb));

		std::unique_ptr<void, void(*)(void*)> userdata(
			rawPtr,
			[](void* ptr) { delete static_cast<Decayed*>(ptr); }
		);

		auto wrapper = [](void* ud, const T& e)
			{
				(*static_cast<Decayed*>(ud))(e);
			};

		auto& vec = std::get<std::vector<Callback<T>>>(m_Listeners);
		vec.push_back({ wrapper, std::move(userdata)});
	}

	void Dispatch(const Event& event)
	{
		std::visit([&](auto&& ev)
		{
			using T = std::decay_t<decltype(ev)>;
			auto& vec = std::get<std::vector<Callback<T>>>(m_Listeners);
			for (auto& cb : vec)
				cb.fn(cb.userdata.get(), ev);
		}, event);
	}

private:
	std::tuple<
		std::vector<Callback<Event1>>,
		std::vector<Callback<Event2>>,
		std::vector<Callback<Event3>>
	> m_Listeners;
};

class EventQueue {
public:
	template<typename T>
	void Push(const T& e)
	{
		m_Events.emplace(e);
	}

	void Process(EventBus& bus)
	{
		while (!m_Events.empty())
		{
			bus.Dispatch(m_Events.front());
			m_Events.pop();
		}
	}

private:
	std::queue<Event> m_Events;
};