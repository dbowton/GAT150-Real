#include "EventSystem.h"
#include "Object/Object.h"

namespace dwb
{
	void EventSystem::StartUp()
	{

	}

	void EventSystem::ShutDown()
	{

	}

	void EventSystem::Update(float dt)
	{

	}

	void EventSystem::Subscribe(const std::string& name, function_t function, Object* receiver)
	{
		Observer observer;
		observer.function = function;
		observer.receiver = receiver;

		observers[name].push_back(observer);
	}
	
	void EventSystem::Notify(const Event& event)
	{
		auto& eventObservers = observers[event.name];
	
		for (auto& observer : eventObservers)
		{
			if (event.receiver == nullptr || event.receiver == observer.receiver)
			{
				observer.function(event);
			}
		}
	}
}