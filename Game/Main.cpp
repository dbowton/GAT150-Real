#include "Engine.h"

#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>

int main(int, char**)
{
	dwb::Timer timer;

	dwb::Engine engine;
	engine.StartUp();
	engine.Get<dwb::Renderer>()->Create("GAT150", 800, 600);

	std::cout << timer.ElapsedTicks() << std::endl;

	dwb::Scene scene;
	scene.engine = &engine;

	dwb::SetFilePath("../Resources");

	std::shared_ptr<dwb::Texture> texture = engine.Get<dwb::ResourceSystem>()->Get<dwb::Texture>("sf2.png", engine.Get<dwb::Renderer>());

	for (int i = 0; i < 10; i++)
	{
		dwb::Transform transform{ {dwb::RandomRangeInt(0, 800), dwb::RandomRangeInt(0, 600)}, dwb::RandomRange(0.0f, 360.0f), 1.0f };
		std::unique_ptr<dwb::Actor> actor = std::make_unique<dwb::Actor>(transform, texture);

		scene.addActor(std::move(actor));
	}

	bool quit = false;
	SDL_Event event;
	float quitTime = engine.time.time + 3.0f;

	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Update();
		scene.Update(engine.time.deltaTime);

		if (engine.Get<dwb::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == dwb::InputSystem::eKeyState::Pressed)
		{
			quit = true;
		}

		if (engine.Get<dwb::InputSystem>()->GetButtonState((int) dwb::InputSystem::eMouseButton::Left) == dwb::InputSystem::eKeyState::Pressed)
		{
			dwb::Vector2 position = engine.Get<dwb::InputSystem>()->GetMousePosition();
			std::cout << position.x << " " << position.y << std::endl;
		}


		if (engine.time.time >= quitTime) quit = true;
		engine.time.timeScale = 1;

		engine.Get<dwb::Renderer>()->BeginFrame();

		scene.Draw(engine.Get<dwb::Renderer>());
		engine.Draw(engine.Get<dwb::Renderer>());

		engine.Get<dwb::Renderer>()->EndFrame();

		//for (int i = 0; i < 50; i++) 
		//{
		//	SDL_Rect src{ 32,64, 32,64 };

		//	SDL_Rect dest{ dwb::RandomRangeInt(0,screen.x), dwb::RandomRangeInt(0,screen.y), 64,96 };
		//	SDL_RenderCopy(renderer, texture, &src, &dest);
		//}
	}

	SDL_Quit();
	return 0;
}