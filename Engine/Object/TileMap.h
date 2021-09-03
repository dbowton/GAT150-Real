#pragma once
#include "Object.h"
#include "Core/Serailizable.h"
#include <vector>S

namespace dwb
{
	class TileMap : public Object, public ISerializable
	{
	public:
		void Create() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	
	public:
		class Scene* scene = nullptr;

		int numTilesX{ 0 };
		int numTilesY{ 0 };
		Vector2 offset;
		Vector2 size;

		std::vector<std::string> tileNames;
		std::vector<int> tiles;
	};
}