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

	dwb::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	dwb::SetFilePath("../Resources");


	//events
	engine->Get<dwb::EventSystem>()->Subscribe("add_score", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
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


	switch (state)
	{
	case Game::eState::Reset:
		Reset();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	default:
		break;
	}

	//update score

	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<dwb::Renderer>()->BeginFrame();
	
	scene->Draw(engine->Get<dwb::Renderer>());
	engine->Draw(engine->Get<dwb::Renderer>());

	engine->Get<dwb::Renderer>()->EndFrame();
}

void Game::Reset()
{
	scene->removeAllActors();

	rapidjson::Document document;
	bool success = dwb::json::Load("title.txt", document);
	assert(success);

	scene->Read(document);

	state = eState::Title;
}

void Game::Title()
{
	if (engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == dwb::InputSystem::eKeyState::Pressed)
	{
		auto title = scene->findActor("Title");
		assert(title);
		title->active = false;

		state = eState::StartGame;
	}
}

void Game::StartGame()
{
	rapidjson::Document document;
	bool success = dwb::json::Load("scene.txt", document);
	assert(success);

	scene->Read(document);

	dwb::TileMap tileMap;
	tileMap.scene = scene.get();
	success = dwb::json::Load("map.txt", document);
	assert(success);
	tileMap.Read(document);
	tileMap.Create();

	stateTimer = 0;
	score = 50;
	points = 0;
	state = eState::StartLevel;
}

void Game::StartLevel()
{
	stateTimer += engine->time.deltaTime;
	
	if (stateTimer >= 1)
	{
		auto player = dwb::ObjectFactory::Instance().Create<dwb::Actor>("Player");
		player->transform.position = { 400, 350 };
		scene->addActor(std::move(player));

		spawnTimer = 2;

		state = eState::Level;
	}
}

void Game::Level()
{
	spawnTimer -= engine->time.deltaTime;

	if (spawnTimer <= 0)
	{
		spawnTimer = 2;

		auto coin = dwb::ObjectFactory::Instance().Create<dwb::Actor>("coin");
		coin->transform.position = { dwb::RandomRangeInt(100, 700), 150 };
		scene->addActor(std::move(coin));
	}

	auto scoreActor = scene->findActor("Score");
	if (scoreActor)
	{
		scoreActor->GetComponent<dwb::TextComponent>()->SetText("Score: " + std::to_string(score));
	}

	auto pointActor = scene->findActor("Points");
	if (pointActor)
	{
		pointActor->GetComponent<dwb::TextComponent>()->SetText("Points: " + std::to_string((int)points));
	}

	if (score <= 0)
	{
		state = eState::PlayerDead;
	}
	else
	{
		points += engine->time.deltaTime;
	}
}

void Game::PlayerDead()
{
	state = eState::GameOver;
}

void Game::GameOver()
{
	scene->findActor("Player")->GetComponent<PlayerComponent>()->speed = 0;
	scene->findActor("Bat")->GetComponent<EnemyComponent>()->speed = 0;
	scene->findActor("Blob")->GetComponent<EnemyComponent>()->speed = 0;

	if (engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == dwb::InputSystem::eKeyState::Pressed)
	{
		state = eState::Reset;
	}
}

void Game::OnAddScore(const dwb::Event& event)
{
	score += std::get<int>(event.data);
}