#include "Projectile.h"
#include "Math/MathUtils.h"
#include "Engine.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	destroy = (lifetime <= 0);

	transform.position += (dwb::Vector2::Rotate(dwb::Vector2::right, transform.rotation) * speed) * dt;
	transform.position.x = dwb::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = dwb::Wrap(transform.position.y, 0.0f, 600.0f);
}