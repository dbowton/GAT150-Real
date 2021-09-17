#pragma once
#include "Object/Object.h"
#include "Core/Serailizable.h"

namespace dwb
{
	class Actor;

	class Component : public Object, public ISerializable
	{
	public:
		virtual void Update() = 0;

	public:
		Actor* owner{ nullptr };
	};
}