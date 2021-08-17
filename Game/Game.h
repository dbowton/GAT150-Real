#pragma once
#include "Engine.h"

class Game
{
public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();
	
	bool IsQuit() { return quit; }

public:
	std::unique_ptr<dwb::Engine> engine;
	std::unique_ptr<dwb::Scene> scene;

private:
	bool quit = false;
};