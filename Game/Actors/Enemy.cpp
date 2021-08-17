#include "Enemy.h"
#include "Player.h"
#include "Math/MathUtils.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	if (scene->getActor<Player>())
	{
		//

		dwb::Vector2 direction = scene->getActor<Player>()->transform.position - transform.position;
		dwb::Vector2 forward = dwb::Vector2::Rotate(dwb::Vector2::right, transform.rotation);

		float turnAngle = dwb::Vector2::SignedAngle(forward, direction.Normalized());
		float workingRotation = transform.rotation + turnAngle * (3 * dt);

		transform.rotation = dwb::Lerp(transform.rotation, workingRotation, dwb::Random());
		
		//transform.rotation = dwb::Lerp(transform.rotation, transform.rotation + turnAngle, dt * 2);

		float angle = dwb::Vector2::Angle(direction.Normalized(), forward);


		fireTimer -= dt;
		if (canShoot && fireTimer <= 0 && angle <= dwb::DegToRad(8))
		{
			fireTimer = fireRate;

			std::vector<dwb::Vector2> pewPoints = { {-5,-5}, {5,-5}, {0,8}, {-5,-5} };
			//std::shared_ptr<dwb::Texture> pewShape = std::make_shared<dwb::Texture>(pewPoints);
			std::shared_ptr<dwb::Texture> pewShape = scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/darkShip.png", scene->engine->Get<dwb::Renderer>());

			//std::shared_ptr<dwb::Texture> texture = scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/fighter.png", scene->engine->Get<dwb::Renderer>());

			dwb::Transform t = transform;
			//t.scale = 2.0f;

			//const dwb::Transform& transform, std::shared_ptr<dwb::Texture> texture, float speed


			std::shared_ptr<dwb::Texture> texture = scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/darkTorpedo.png", scene->engine->Get<dwb::Renderer>());
			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, texture, 600.0f);
			projectile->tag = "Enemy";

			scene->addActor(std::move(projectile));
		}
	}

	transform.position += (dwb::Vector2::Rotate(dwb::Vector2::right, transform.rotation) * speed) * dt;
	transform.position.x = dwb::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = dwb::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::onCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		actor->destroy = true;

		destroy = true;

		//SDL_Surface* surface

		std::shared_ptr<dwb::Texture> particleTexture = scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/flames.png", scene->engine->Get<dwb::Renderer>());
		scene->engine->Get<dwb::ParticleSystem>()->Create(transform.position, 10, 1, particleTexture, 50);
		//scene->engine->Get<dwb::AudioSystem>()->PlayAudio("explosion");
		scene->engine->Get<dwb::AudioSystem>()->PlayAudio("Enemy_Killed");

		dwb::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<dwb::EventSystem>()->Notify(event);
	}
}
