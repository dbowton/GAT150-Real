#include "EnemyComponent.h"
#include "Engine.h"

using namespace dwb;

void EnemyComponent::Update()
{
	Actor* player = owner->scene->findActor("Player");
	
	if (player) {
		Vector2 force;
		
		if (canFly)
		{
			Vector2 direction = player->transform.position - owner->transform.position;
			force = direction.Normalized() * speed;
		}
		else
		{
			if (player->transform.position.x > owner->transform.position.x) force.x += speed;
			else force.x -= speed;
		}

		PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
		assert(physicsComponent);

		SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
		assert(spriteAnimationComponent);

		if(force.x < 0) spriteAnimationComponent->StartSequence("Walk_Left");
		else spriteAnimationComponent->StartSequence("Walk_Right");

		physicsComponent->ApplyForce(force);
	}
}

bool EnemyComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	JSON_READ(value, canFly);

	return true;
}