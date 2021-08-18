#pragma once

//Audio
#include "Audio/AudioSystem.h"


//Graphics
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/ParticleSystem.h"
#include "Graphics/Font.h"

//core
#include "Core/Utilities.h"
#include "Core/FileSystem.h"
#include "Core/Timer.h"

//Base
#include "Object/Actor.h"
#include "Object/Object.h"
#include "Framework/System.h"

//Components
#include "Component/SpriteComponent.h"
#include "Component/SpriteAnimationComponent.h"
#include "Component/PhysicsComponent.h"

//Systems
#include "Framework/EventSystem.h"
#include "Input/InputSystem.h"

//Resource
#include "Resource/ResourceSystem.h"

#include "Object/Scene.h"

//Math
#include "Math/Color.h"
#include "Math/MathUtils.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"

#include <vector>
#include <algorithm>
#include <memory>

namespace dwb
{
	class Engine
	{
	public:
		void StartUp();
		void ShutDown();

		void Update();
		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};
	
	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}