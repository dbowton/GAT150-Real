#include "Engine.h"

namespace dwb
{
	void Engine::StartUp()
	{
		systems.push_back(std::make_unique<EventSystem>());
		systems.push_back(std::make_unique<ResourceSystem>());

		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->StartUp(); });
	}
	void Engine::ShutDown()
	{
		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->ShutDown(); });
	}
	void Engine::Update(float dt)
	{
		std::for_each(systems.begin(), systems.end(), [dt](auto& system) {system->Update(dt); });
	}

	void Engine::Draw()
	{

	}
}