#pragma once
#include "Object.h"
#include "Core/Serailizable.h"
#include <list>
#include <memory>
#include <vector>

namespace dwb
{
	class Actor;
	class Engine;
	class Renderer;

	class Scene : public Object, public ISerializable
	{
	public:
		void Update(float dt);
		void Draw(Renderer* renderer);

		void addActor(std::unique_ptr<Actor> actor);
		void removeActor(Actor* actor);
		void removeAllActors();

		Actor* findActor(const std::string& name);

		template<typename T>
		T* getActor();

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		template<typename T>
		std::vector<T*> getActors();

	public:
		Engine* engine{nullptr};

	private:
		std::vector<std::unique_ptr<Actor>> actors;
		std::vector<std::unique_ptr<Actor>> newActors;
	};

	template<typename T>
	inline T* Scene::getActor()
	{
		for (auto& actor : actors)
		{
			if(dynamic_cast<T*>(actor.get())) return dynamic_cast<T*>(actor.get());
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::getActors()
	{
		std::vector<T*> result;
		
		for (auto& actor : actors)
		{
			if (dynamic_cast<T*>(actor.get())) result.push_back(dynamic_cast<T*>(actor.get()));
		}

		return result;
	}
}