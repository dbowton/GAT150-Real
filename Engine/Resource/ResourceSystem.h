#pragma once
#include "Framework/System.h"
#include "Resource.h"
#include <string>
#include <map>
#include <memory>
#include <algorithm>

namespace dwb
{
	class ResourceSystem : public System
	{
	public:
		void StartUp() override {};
		void ShutDown() override {};
		void Update(float dt) override {};
		
		template<typename T>
		std::shared_ptr<T> Get(const std::string& name, void* data = nullptr);

		void Add(const std::string& name, std::shared_ptr<Resource> resource);

	private:
		std::map<std::string, std::shared_ptr<Resource>> resources;
	};

	template<typename T>
	inline std::shared_ptr<T> ResourceSystem::Get(const std::string& name, void* data)
	{
		if (resources.find(string_toLower(name)) != resources.end())
		{
			return std::dynamic_pointer_cast<T>(resources[string_toLower(name)]);
		}

		std::shared_ptr resource = std::make_shared<T>();
		resource->Load(name, data);
		resources[string_toLower(name)] = resource;

		return resource;
	}

	inline void ResourceSystem::Add(const std::string& name, std::shared_ptr<Resource> resource)
	{
		resources[string_toLower(name)] = resource;
	}

}