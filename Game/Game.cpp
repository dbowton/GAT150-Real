#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"

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
	
	//register da classes
	REGISTER_CLASS(PlayerComponent);
	REGISTER_CLASS(EnemyComponent);
	REGISTER_CLASS(PickupComponent);

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

	for (int i = 0; i < 10; i++)
	{
		auto actor = dwb::ObjectFactory::Instance().Create<dwb::Actor>("coin");
		actor->transform.position = { dwb::RandomRangeInt(0, 800), dwb::RandomRangeInt(500, 550) };
		scene->addActor(std::move(actor));
	}
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