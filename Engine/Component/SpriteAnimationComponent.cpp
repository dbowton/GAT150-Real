#include "SpriteAnimationComponent.h"
#include "Engine.h"

namespace dwb
{
	void SpriteAnimationComponent::Update()
	{		
		frameTime = 1.0f / fps;

		frameTimer += owner->scene->engine->time.deltaTime;
		if (frameTimer >= frameTime)
		{
			frameTimer = 0;
			frame++;

			if (frame >= numFramesX * numFramesY) frame = 0;
		}

		Vector2 size = texture->GetSize();
		Vector2 frameCount{ numFramesX, numFramesY };
		Vector2 frameSize = size / frameCount;

		rect.x = static_cast<int>((frame % numFramesX) * frameSize.x); 
		rect.y = static_cast<int>((frame / numFramesX) * frameSize.y); 
		rect.w = static_cast<int>(frameSize.x); 
		rect.h = static_cast<int>(frameSize.y);
	}
	
	void SpriteAnimationComponent::Draw(Renderer* renderer)
	{
		renderer->Draw(texture, rect, owner->transform);
	}
	bool SpriteAnimationComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool SpriteAnimationComponent::Read(const rapidjson::Value& value)
	{
		SpriteComponent::Read(value);

		int framesPerSecond;
		JSON_READ(value, framesPerSecond);
		fps = framesPerSecond;

		int numXFrames;
		JSON_READ(value, numXFrames);
		numFramesX = numXFrames;

		int numYFrames;
		JSON_READ(value, numYFrames);
		numFramesY = numYFrames;

		return true;
	}
}