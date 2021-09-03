#pragma once
#include "GraphicsComponent.h"
#include <memory>

namespace dwb
{
	class Texture;

	class SpriteComponent : public GraphicsComponent
	{
	public:
		std::unique_ptr<Object> Clone() const { return std::make_unique<SpriteComponent>(*this); };

		void Update() override;
		void Draw(Renderer* renderer) override;

	public:
		std::shared_ptr<Texture> texture;
		SDL_Rect rect;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	};
}