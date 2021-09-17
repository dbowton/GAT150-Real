#include "PickupComponent.h"
#include "Engine.h"

using namespace dwb;

void PickupComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickupComponent::OnCollisionEnter, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "audio/coin.wav");
}

PickupComponent::~PickupComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
}

void PickupComponent::Update()
{

}

void PickupComponent::OnCollisionEnter(const Event& event)
{
	Actor* actor = reinterpret_cast<Actor*>(std::get<void*>(event.data));

	if (string_compare_i(actor->tag, "player"))
	{
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");

		Event event;
		event.name = "add_score";
		event.data = 10;

		owner->scene->engine->Get<dwb::EventSystem>()->Notify(event);

		owner->destroy = true;
	}
}

bool PickupComponent::Write(const rapidjson::Value& value) const
{
	return false;
}
	
bool PickupComponent::Read(const rapidjson::Value& value)
{
	return true;
}