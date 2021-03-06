#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"

class PlayerComponent : public dwb::Component
{
public:
	virtual ~PlayerComponent();

	std::unique_ptr<Object> Clone() const { return std::make_unique<PlayerComponent>(*this); };

	void Create() override;
	virtual void Update() override;

	virtual void onCollisionEnter(const dwb::Event& event);
	virtual void onCollisionExit(const dwb::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0 };
	float jump{ 0 };

private:
	std::list<dwb::Actor*> contacts;
};