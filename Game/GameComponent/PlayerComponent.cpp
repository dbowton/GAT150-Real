#include "PlayerComponent.h"
#include "Engine.h"

using namespace dwb;

PlayerComponent::~PlayerComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void PlayerComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PlayerComponent::onCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PlayerComponent::onCollisionExit, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "audio/hurt.wav");
}

void PlayerComponent::Update()
{
	Vector2 force = Vector2::zero;
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)
	{
		force.x -= speed;
	}

	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held)
	{
		force.x += speed;
	}

	if (contacts.size() > 0 && owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == InputSystem::eKeyState::Pressed)
	{
		force.y -= 500;
	}

	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);

	physicsComponent->ApplyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
	assert(spriteAnimationComponent);

	if (force.x > 0) spriteAnimationComponent->StartSequence("walk_right");
	else if (force.x < 0) spriteAnimationComponent->StartSequence("walk_left");
	else spriteAnimationComponent->StartSequence("idle");
}

void PlayerComponent::onCollisionEnter(const Event& event)
{
	Actor* actor = reinterpret_cast<Actor*>(std::get<void*>(event.data));

	if (string_compare_i(actor->tag, "ground"))
	{
		contacts.push_back(actor);
	}

	if (string_compare_i(actor->tag, "enemy"))
	{
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("hurt");
	}
}

void PlayerComponent::onCollisionExit(const Event& event)
{
	Actor* actor = reinterpret_cast<Actor*>(std::get<void*>(event.data));

	if (string_compare_i(actor->tag, "ground"))
	{
		contacts.remove(actor);
	}
}

bool PlayerComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);

	return true;
}
