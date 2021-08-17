#pragma once

#include "Object/Actor.h"

class Projectile : public dwb::Actor
{
public:
	Projectile(const dwb::Transform& transform, std::shared_ptr<dwb::Texture> texture, float speed) : dwb::Actor{ transform, texture }, speed{ speed } {}

	void Update(float dt) override;

private:
	float lifetime{ 2 };
	float speed{ 300 };
};