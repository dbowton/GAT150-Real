#pragma once
#include "Component/Component.h"

namespace dwb
{
	class Renderer;

	class GraphicsComponent : public Component
	{
	public:
		virtual void Draw(Renderer* renderer) = 0;
	};
}