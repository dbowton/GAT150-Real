#include "SpriteComponent.h"
#include "Graphics/Renderer.h"
#include "Engine.h"
#include "Object/Actor.h"

namespace dwb
{
	void SpriteComponent::Update()
	{
		
	}
	
	void SpriteComponent::Draw(Renderer* renderer)
	{
		renderer->Draw(texture, owner->transform);
	}
	bool SpriteComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool SpriteComponent::Read(const rapidjson::Value& value)
	{
		std::string textureName;
		JSON_READ(value, textureName);

		texture = owner->scene->engine->Get<ResourceSystem>()->Get<Texture>(textureName, owner->scene->engine->Get<Renderer>());

		return true;
	}
}