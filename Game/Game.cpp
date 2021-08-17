#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"

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
	font = engine->Get<dwb::ResourceSystem>()->Get<dwb::Font>("fonts/roboto.ttf", &fontSize);

	dwb::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	dwb::SetFilePath("../Resources");

	//---------------------------------------------------------

	dwb::Timer timer;
	std::cout << timer.ElapsedTicks() << std::endl;

	engine->Get<dwb::AudioSystem>()->AddAudio("explosion", "Audio/Enemy_Killed.wav");


	engine->Get<dwb::AudioSystem>()->AddAudio("song", "Audio/song.mp3");
	musicChannel = engine->Get<dwb::AudioSystem>()->PlayAudio("song", 1, 1, true);

	//---------------------------------------------------------

	//game
	engine->Get<dwb::AudioSystem>()->AddAudio("Enemy_Killed", "Enemy_Killed.wav");
	engine->Get<dwb::AudioSystem>()->AddAudio("Player_Fire", "Player_Fire.wav");

	engine->Get<dwb::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<dwb::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->removeAllActors();
	engine->ShutDown();
}

void Game::Update()
{
	float dt = engine->time.deltaTime;
	std::shared_ptr<dwb::Texture> texture;

	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		if (engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == dwb::InputSystem::eKeyState::Pressed)
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;

		//Player	
		texture = engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/lightShip.png", engine->Get<dwb::Renderer>());
		scene->addActor(std::make_unique<Player>(dwb::Transform{ dwb::Vector2{400.0f, 300.0f}, 0.0f, 1.0f }, texture, 250.0f));

		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{
		currentLevel++;
		UpdateLevelStart(dt);
		state = eState::Game;
		break;
	}
		break;
	case Game::eState::Game:
		
		if (scene->getActors<Enemy>().size() == 0 && currentLevel >= maxLevel)
		{
			state = eState::GameOver;
		}
		else if(scene->getActors<Enemy>().size() == 0)
		{
			state = eState::StartLevel;
		}
		break;
	case Game::eState::GameOver:
		musicChannel.Stop();
		break;
	default:
		break;
	}

	engine->Update();
	scene->Update(dt);

	//---------------------------------------------------------
	if (engine->Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == dwb::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}

	if (engine->Get<dwb::InputSystem>()->GetButtonState((int)dwb::InputSystem::eMouseButton::Left) == dwb::InputSystem::eKeyState::Pressed)
	{
		musicChannel.SetPitch(dwb::RandomRange(0.2f, 2.0f));
		engine->Get<dwb::AudioSystem>()->PlayAudio("explosion", 1, dwb::RandomRange(0.2f, 2.0f));
		dwb::Vector2 position = engine->Get<dwb::InputSystem>()->GetMousePosition();

		engine->Get<dwb::ParticleSystem>()->Create(position, 20, 3, engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/devito.png", engine->Get<dwb::Renderer>()), 200);
		std::cout << position.x << " " << position.y << std::endl;
	}
}

void Game::Draw()
{
	switch (state)
	{
	case Game::eState::Title:
		fontSize = 128;

		font->Load("fonts/curly.ttf", &fontSize);

		t.position = { 400, 300 };

		writtenTexture = std::make_shared<dwb::Texture>(engine->Get<dwb::Renderer>());;
		writtenTexture->Create(font->CreateSurface("PewPew Destroyer", dwb::Color::red));
		engine->Get<dwb::ResourceSystem>()->Add("writtenTexture", writtenTexture);
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		fontSize = 14;

		font->Load("fonts/raleway.ttf", &fontSize);

		scorePos.position = { 60, 30 };
		healthPos.position = { 60, 50 };
		livesPos.position = { 60, 70 };

		scoreText = std::make_shared<dwb::Texture>(engine->Get<dwb::Renderer>());
		healthText = std::make_shared<dwb::Texture>(engine->Get<dwb::Renderer>());
		livesText = std::make_shared<dwb::Texture>(engine->Get<dwb::Renderer>());

		scoreText->Create(font->CreateSurface(("Score: " + std::to_string(score)).c_str(), dwb::Color::white));
		healthText->Create(font->CreateSurface(("Health: " + std::to_string(scene->getActor<Player>()->getHealth())).c_str(), dwb::Color::white));
		livesText->Create(font->CreateSurface(("Lives: " + std::to_string(lives)).c_str(), dwb::Color::white));

		engine->Get<dwb::ResourceSystem>()->Add("scoreText", scoreText);
		engine->Get<dwb::ResourceSystem>()->Add("healthText", healthText);
		engine->Get<dwb::ResourceSystem>()->Add("livesText", livesText);
		break;
	case Game::eState::GameOver:

		

		if (scene->getActors<Enemy>().size() == 0)
		{
			fontSize = 64;

			font->Load("fonts/curly.ttf", &fontSize);

			t.position = { 400, 300 };

			writtenTexture = std::make_shared<dwb::Texture>(engine->Get<dwb::Renderer>());;
			writtenTexture->Create(font->CreateSurface("Victory", dwb::Color::green));
			engine->Get<dwb::ResourceSystem>()->Add("writtenTexture", writtenTexture);
		}
		else
		{
			fontSize = 64;

			font->Load("fonts/curly.ttf", &fontSize);

			t.position = { 400, 300 };

			writtenTexture = std::make_shared<dwb::Texture>(engine->Get<dwb::Renderer>());;
			writtenTexture->Create(font->CreateSurface("Defeat", dwb::Color::red));
			engine->Get<dwb::ResourceSystem>()->Add("writtenTexture", writtenTexture);

			if(scene->getActor<Player>()) scene->getActor<Player>()->destroy = true;
		}
		break;
	default:
		break;
	}

	engine->Get<dwb::Renderer>()->BeginFrame();

	if (state == Game::eState::Title)
	{
		engine->Get<dwb::Renderer>()->Draw(writtenTexture, t);
	}
	else if(state == Game::eState::Game)
	{
		engine->Get<dwb::Renderer>()->Draw(scoreText, scorePos);
		engine->Get<dwb::Renderer>()->Draw(healthText, healthPos);
		engine->Get<dwb::Renderer>()->Draw(livesText, livesPos);
	}
	else if (state == Game::eState::GameOver)
	{
		engine->Get<dwb::Renderer>()->Draw(writtenTexture, t);
	}
	
	scene->Draw(engine->Get<dwb::Renderer>());
	engine->Draw(engine->Get<dwb::Renderer>());

	engine->Get<dwb::Renderer>()->EndFrame();
}

void Game::UpdateLevelStart(float dt)
{		

	std::shared_ptr<dwb::Texture> enemyTexture = engine->Get<dwb::ResourceSystem>()->Get<dwb::Texture>("Assets/darkShip.png", engine->Get<dwb::Renderer>());

	//Shooty Enemies
	for (int i = 0; i < 1 * (currentLevel + 1); i++)
	{
		scene->addActor(std::make_unique<Enemy>(dwb::Transform{ dwb::Vector2{dwb::RandomRange(0.0f, 800.0f), dwb::RandomRange(0.0f, 300.0f)}, dwb::RandomRange(0.0f, 800.0f), 1.0f }, enemyTexture, 100.0f, true));
	}
		
	//Non-Shooty Enemies
	for (int i = 0; i < 2 * (currentLevel + 1); i++)
	{
		scene->addActor(std::make_unique<Enemy>(dwb::Transform{ dwb::Vector2{dwb::RandomRange(0.0f, 800.0f), dwb::RandomRange(0.0f, 300.0f)}, dwb::RandomRange(0.0f, 800.0f), 1.0f }, enemyTexture, 150.0f, false));
	}
}

void Game::OnAddPoints(const dwb::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const dwb::Event& event)
{
	if (lives >= 1)
	{
		lives--;
	}

	std::cout << lives << std::endl;
	
	if (lives <= 0)
	{
		state = eState::GameOver;
	}

	if (state == eState::GameOver)
	{
		std::cout << "Over" << std::endl;
	}
	else
	{
		std::cout << "Danger" << std::endl;
	}
}