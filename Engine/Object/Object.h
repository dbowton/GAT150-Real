#pragma once

namespace dwb
{
	class Object
	{
	public:
		virtual ~Object() {}

		virtual void Create() {}
	};
}