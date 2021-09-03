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
		renderer->Draw(texture, rect, owner->transform);
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

		JSON_READ(value, rect);
		if (rect.x == 0 && rect.y == 0 && rect.w == 0 && rect.h == 0)
		{
			Vector2 size = texture->GetSize();

			rect.w = (int) size.x;
			rect.h = (int) size.y;
		}

		return true;
	}
}