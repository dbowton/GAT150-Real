#pragma once
#include "document.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <vector>
#include <string>

#define JSON_READ(value, data) dwb::json::Get(value, #data, data);

namespace dwb
{
	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document);

		bool Get(const rapidjson::Value& value, const std::string& name, int& data);
		bool Get(const rapidjson::Value& value, const std::string& name, float& data);
		bool Get(const rapidjson::Value& value, const std::string& name, bool& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Color& data);

		bool Get(const rapidjson::Value& value, const std::string& name, SDL_Rect& data);

		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data);
	}
}