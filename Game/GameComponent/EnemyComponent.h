#pragma once

#pragma once
#include "Component/Component.h"

class EnemyComponent : public dwb::Component
{
public:
	virtual void Update() override;

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0 };
};