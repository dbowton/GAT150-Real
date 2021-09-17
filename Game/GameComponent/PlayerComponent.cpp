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

	owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "audio/grunt.wav");
}

void PlayerComponent::Update()
{
	Vector2 force = Vector2::zero;
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)
	{
		force.x -= speed;
		owner->isLeft = true;
	}

	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held)
	{
		force.x += speed;
		owner->isLeft = false;
	}

	if (contacts.size() > 0 && owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_W) == InputSystem::eKeyState::Pressed)
	{
		force.y -= jump;
	}

	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);

	physicsComponent->ApplyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
	assert(spriteAnimationComponent);

	if (force.x != 0)
	{
		if (owner->isLeft) spriteAnimationComponent->StartSequence("Walk_Left");
		else spriteAnimationComponent->StartSequence("Walk_Right");
	}
	else
	{
		if (owner->isLeft) spriteAnimationComponent->StartSequence("Idle_Left");
		else spriteAnimationComponent->StartSequence("Idle_Right");
	}		
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
		Event event;
		event.name = "add_score";
		event.data = -5;

		owner->scene->engine->Get<dwb::EventSystem>()->Notify(event);


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
	JSON_READ(value, jump);

	return true;
}
