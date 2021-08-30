#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"


class PickupComponent : public dwb::Component
{
public:
	void Create() override;

	std::unique_ptr<Object> Clone() const { return std::make_unique<PickupComponent>(*this); };

	virtual ~PickupComponent();

	virtual void Update() override;

	virtual void OnCollisionEnter(const dwb::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;
};