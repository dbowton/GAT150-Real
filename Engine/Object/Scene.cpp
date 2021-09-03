#include "Scene.h"
#include "Actor.h"
#include "Engine.h"
#include <algorithm>

namespace dwb
{
	void Scene::Update(float dt)
	{
		actors.insert(actors.end(), std::make_move_iterator(newActors.begin()), std::make_move_iterator(newActors.end()));
		newActors.clear();

		if (actors.begin() != actors.end())
		{
			std::for_each(actors.begin(), actors.end(), [dt](auto& actor) {actor->Update(dt); });
		}

		auto iter = actors.begin();
		while (iter != actors.end())
		{
			if ((*iter)->destroy)
			{
				iter = actors.erase(iter);
			}
			else 
			{
				iter++;
			}
		}
	}

	void Scene::Draw(Renderer* renderer)
	{
		std::for_each(actors.begin(), actors.end(), [renderer](auto& actor) {actor->Draw(renderer); });
	}

	void Scene::addActor(std::unique_ptr<Actor> actor)
	{
		actor->scene = this;
		actor->Initialize();

		newActors.push_back(std::move(actor));
	}
	
	void Scene::removeActor(Actor* actor)
	{

	}
	
	void Scene::removeAllActors()
	{
		for (auto& actor : actors)
		{
			actor->destroy = true;
		}
	}

	Actor* Scene::findActor(const std::string& name)
	{
		for (auto& actor : actors)
		{
			if (actor->name == name) return actor.get();
		}
	}

	bool Scene::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool Scene::Read(const rapidjson::Value& value)
	{
		if (value.HasMember("actors") && value["actors"].IsArray())
		{
			for (auto& actorValue : value["actors"].GetArray())
			{
				std::string type;
				JSON_READ(actorValue, type);

				bool prototype = false;
				JSON_READ(actorValue, prototype);

				auto actor = ObjectFactory::Instance().Create<Actor>(type);

				if (actor)
				{
					actor->scene = this;
					actor->Read(actorValue);

					if (prototype)
					{
						std::string name = actor->name;
						ObjectFactory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
					}
					else
					{
						addActor(std::move(actor));
					}
				}
			}
		}

		return true;
	}
}