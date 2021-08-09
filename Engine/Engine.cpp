#include "Engine.h"

namespace dwb
{
	void Engine::StartUp()
	{
		systems.push_back(std::make_unique<Renderer>());
		systems.push_back(std::make_unique<EventSystem>());
		systems.push_back(std::make_unique<ResourceSystem>());
		systems.push_back(std::make_unique<InputSystem>());
		systems.push_back(std::make_unique<ParticleSystem>());

		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->StartUp(); });
	}
	void Engine::ShutDown()
	{
		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->ShutDown(); });
	}
	void Engine::Update()
	{
		time.Tick();
		std::for_each(systems.begin(), systems.end(), [this](auto& system) {system->Update(this->time.deltaTime); });
	}

	void Engine::Draw(Renderer* renderer)
	{
		std::for_each(systems.begin(), systems.end(), [renderer](auto& system) {if (dynamic_cast<GraphicsSystem*>(system.get())) { dynamic_cast<GraphicsSystem*>(system.get())->Draw(renderer); } });
	}
}