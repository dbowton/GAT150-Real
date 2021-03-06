#pragma once

#define REGISTER_CLASS(class) dwb::ObjectFactory::Instance().Register<class>(#class)

//core
#include "Core/Utilities.h"
#include "Core/FileSystem.h"
#include "Core/Json.h"
#include "Core/Timer.h"
#include "Core/Serailizable.h"

//Framework
#include "Framework/EventSystem.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"

//Audio
#include "Audio/AudioSystem.h"
#include "Component/AudioComponet.h"

//Graphics
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/ParticleSystem.h"
#include "Graphics/Font.h"
#include "Component/TextComponent.h"

//physics system
#include "Physics/PhysicsSystem.h"
#include "Component/RBPhysicsComponent.h"

//Objects
#include "Object/Actor.h"
#include "Object/Object.h"
#include "Object/TileMap.h"
#include "Framework/System.h"

//Components
#include "Component/SpriteComponent.h"
#include "Component/SpriteAnimationComponent.h"
#include "Component/PhysicsComponent.h"

//Systems
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
	using ObjectFactory = Singleton<Factory<std::string, Object>>;

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