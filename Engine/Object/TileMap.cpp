#include "TileMap.h"
#include "Engine.h"

namespace dwb
{
	void TileMap::Create()
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			int index = tiles[i];
			if (index == 0) continue;

			auto actor = ObjectFactory::Instance().Create<Actor>(tileNames[index]);
			if (actor)
			{
				int x = i % numTilesX;
				int y = i / numTilesX;

				actor->transform.position = offset + (dwb::Vector2{ x, y } * size);
				scene->addActor(std::move(actor));
			}
		}
	}

	bool TileMap::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool TileMap::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, numTilesX);
		JSON_READ(value, numTilesY);
		JSON_READ(value, size);

		JSON_READ(value, tileNames);
		JSON_READ(value, tiles);

		JSON_READ(value, offset);

		return true;
	}
}