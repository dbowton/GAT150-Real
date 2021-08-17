#include "Game.h"

dwb::Transform t;
std::shared_ptr<dwb::Font> font;

std::shared_ptr<dwb::Texture> writtenTexture;
std::shared_ptr<dwb::Texture> scoreText;
std::shared_ptr<dwb::Texture> healthText;
std::shared_ptr<dwb::Texture> livesText;


dwb::Transform scorePos;
dwb::Transform healthPos;
dwb::Transform livesPos;

int fontSize;

void Game::Initialize()
{
	//make a da Engine
	engine = std::make_unique<dwb::Engine>();
	engine->StartUp();
	engine->Get<dwb::Renderer>()->Create("PewPew Destroyer", 800, 600);

	//make a da Scene
	scene = std::make_unique<dwb::Scene>();
	scene->engine = engine.get();

	//make a da Font
	//font = engine->Get<dwb::ResourceSystem>()->Get<dwb::Font>("fonts/roboto.ttf", &fontSize);

	dwb::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	dwb::SetFilePath("../Resources");


	//actor
	std::unique_ptr<dwb::Actor> actor = std::make_unique<dwb::Actor>(dwb::Transform{ { 400, 300 } });

	{
		std::unique_ptr<dwb::SpriteComponent> component = std::make_unique<dwb::SpriteComponent>();
		component->texture = engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/devito.png", engine->Get<dwb::Renderer>());
		actor->AddComponent(std::move(component));
	}
	{
		std::unique_ptr<dwb::PhysicsComponent> component = std::make_unique<dwb::PhysicsComponent>();
		component->ApplyForce(dwb::Vector2::right * 50);
		actor->AddComponent(std::move(component));
	}

	scene->addActor(std::move(actor));
}

void Game::Shutdown()
{
	scene->removeAllActors();
	engine->ShutDown();
}

void Game::Update()
{
	engine->Update();

	if (engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == dwb::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}

	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<dwb::Renderer>()->BeginFrame();
	
	scene->Draw(engine->Get<dwb::Renderer>());
	engine->Draw(engine->Get<dwb::Renderer>());

	engine->Get<dwb::Renderer>()->EndFrame();
}