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

	rapidjson::Document document;
	bool success = dwb::json::Load("scene.txt", document);
	
	assert(success);

	scene->Read(document);


	//actor
	//std::unique_ptr<dwb::Actor> actor = std::make_unique<dwb::Actor>(dwb::Transform{ { 400, 300 }, 0, 4 });

	//{
	//	auto component = dwb::ObjectFactory::Instance().Create<dwb::SpriteComponent>("SpriteComponent");
	//	component->texture = engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Animated/Character.png", engine->Get<dwb::Renderer>());
	//	actor->AddComponent(std::move(component));

	//	//dwb::SpriteComponent* component = actor->AddComponent<dwb::SpriteComponent>();
	//}
	////{
	////	dwb::PhysicsComponent* component = actor->AddComponent<dwb::PhysicsComponent>();
	////	component->ApplyForce(dwb::Vector2::right * 50);
	////}
	//{
	//	dwb::SpriteAnimationComponent* component = actor->AddComponent<dwb::SpriteAnimationComponent>();
	//	component->texture = engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Animated/Character.png", engine->Get<dwb::Renderer>());
	//	component->fps = 20;
	//	component->numFramesX = 12;
	//	component->numFramesY = 8;
	//}

	//scene->addActor(std::move(actor));
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