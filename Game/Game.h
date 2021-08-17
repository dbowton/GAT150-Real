#pragma once
#include "Engine.h"

class Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver,
	};

public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

private:
	void UpdateLevelStart(float dt);

	void OnAddPoints(const dwb::Event& event);
	void OnPlayerDead(const dwb::Event& event);

public:
	std::unique_ptr<dwb::Engine> engine;
	std::unique_ptr<dwb::Scene> scene;
	bool IsQuit() { return quit; }

private:
	bool quit = false;
	eState state = eState::Title;
	float stateTimer = 0.0f;

	int currentLevel = 0;
	int maxLevel = 3;

	size_t score = 0;
	size_t lives = 0;

	dwb::AudioChannel musicChannel;
	std::shared_ptr<dwb::Texture> particleTexture;
	std::shared_ptr<dwb::Texture> textTexture;
};