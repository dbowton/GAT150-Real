#include "Player.h"
#include "Projectile.h"
#include "Math/MathUtils.h"
#include "Input/InputSystem.h"
#include "Enemy.h"
#include <memory>

#include "Engine.h"

Player::Player(const dwb::Transform& transform, std::shared_ptr<dwb::Texture> texture, float speed) : dwb::Actor{ transform, texture }, speed{ speed }
{
	health = 500;
}

void Player::Initialize()
{
	{
		std::unique_ptr exhaust = std::make_unique<Actor>();
		exhaust->transform.localPosition = { -4, 0 };
		exhaust->transform.localRotation = dwb::DegToRad(180);
		AddChild(std::move(exhaust));
	}

	{
		std::unique_ptr pewPoint = std::make_unique<Actor>();
		pewPoint->transform.localPosition = { 3, 3 };
		AddChild(std::move(pewPoint));

		pewPoint = std::make_unique<Actor>();
		pewPoint->transform.localPosition = { 3, -3 };
		AddChild(std::move(pewPoint));
	}
}

void Player::Update(float dt)
{
	Actor::Update(dt);
	//children[3]->transform.localRotation += 5 * dt;

	//move
	float thrust;

	if(scene->engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == dwb::InputSystem::eKeyState::Held)
	{ 
		if (speed < 100) speed = 100;
		if (speed < 400) speed *= 1.01f;
	}
	else if (scene->engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_S) == dwb::InputSystem::eKeyState::Held && speed > 250)
	{
		speed *= .9f;
	}
	else if(speed >= 400)
	{
		speed *= 0.99f;
	}
	thrust = speed;

	if (scene->engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == dwb::InputSystem::eKeyState::Held) transform.rotation -= (2 * dt);
	if (scene->engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == dwb::InputSystem::eKeyState::Held) transform.rotation += (2 * dt);


	if (scene->engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_R) == dwb::InputSystem::eKeyState::Pressed) {
		transform.position.x = 400;
		transform.position.y = 300;
		speed = 300;
	}

	dwb::Vector2 acceleration;
	
	acceleration = (dwb::Vector2::Rotate(dwb::Vector2::right, transform.rotation) * thrust);
	//dwb::Vector2 gravity = (dwb::Vector2{ 400, 300 } - transform.position).Normalized() * 200;
	/*dwb::Vector2 gravity = dwb::Vector2::down * 50;
	acceleration += gravity;*/
	
	
	velocity += acceleration * dt;
	transform.position += velocity * dt;
	velocity *= .99f;

	transform.position.x = dwb::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = dwb::Wrap(transform.position.y, 0.0f, 600.0f);

	//fire
	fireTimer -= dt;
	if (fireTimer <= 0 && scene->engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == dwb::InputSystem::eKeyState::Held)
	{
		fireTimer = fireRate;

		{
			dwb::Transform t = children[1]->transform;

			std::shared_ptr<dwb::Texture> projectileTexture = scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/lightTorpedo.png", scene->engine->Get<dwb::Renderer>());
			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, projectileTexture, 600.0f);
			projectile->tag = "Player";

			scene->addActor(std::move(projectile));

			speed *= 0.95f;
		}

		{
			dwb::Transform t = children[2]->transform;

			std::shared_ptr<dwb::Texture> projectileTexture = scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/lightTorpedo.png", scene->engine->Get<dwb::Renderer>());
			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, projectileTexture, 600.0f);
			projectile->tag = "Player";

			scene->addActor(std::move(projectile));

			speed *= 0.95f;
		}

		scene->engine->Get<dwb::AudioSystem>()->PlayAudio("Player_Fire");
	}

	std::vector<dwb::Color> colors = { dwb::Color::white, dwb::Color::blue, dwb::Color::red };

	std::shared_ptr<dwb::Texture> particleTexture = scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/flamesSmall.png", scene->engine->Get<dwb::Renderer>());
	scene->engine->Get<dwb::ParticleSystem>()->Create(children[0]->transform.position, 2, 0.2f, particleTexture, 50, transform.rotation, dwb::DegToRad(15));
}

void Player::onCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor))
	{
		actor->destroy = true;

		std::shared_ptr<dwb::Texture> particleTexture = scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/flames.png", scene->engine->Get<dwb::Renderer>());
		scene->engine->Get<dwb::ParticleSystem>()->Create(transform.position, 10, 0.5f, particleTexture, 50);
		scene->engine->Get<dwb::AudioSystem>()->PlayAudio("explosion");
		scene->engine->Get<dwb::AudioSystem>()->PlayAudio("Enemy_Killed");

		health -= 200;
	}

	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy")
	{
		actor->destroy = true;

		std::shared_ptr<dwb::Texture> particleTexture = scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/flames.png", scene->engine->Get<dwb::Renderer>());
		scene->engine->Get<dwb::ParticleSystem>()->Create(transform.position, 10, 0.5f, particleTexture, 50);
		scene->engine->Get<dwb::AudioSystem>()->PlayAudio("explosion");

		health -= 100;
	}

	if (health <= 0) {
		dwb::Event event;
		event.name = "PlayerDead";
		event.data = std::string("yes I am dead!");
		scene->engine->Get<dwb::EventSystem>()->Notify(event);

		health = 500;
	}
}