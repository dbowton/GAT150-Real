#pragma once

//Audio
//#include "Audio/AudioSystem.h"

//core
#include "Core/FileSystem.h"

//Base
#include "Object/Actor.h"
#include "Object/Object.h"
#include "Framework/System.h"

//Systems
#include "Framework/EventSystem.h"

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

		void Update(float dt);
		void Draw();

		template<typename T>
		T* Get();

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