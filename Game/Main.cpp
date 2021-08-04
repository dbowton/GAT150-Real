#include "Engine.h"

#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>

int main(int, char**)
{
	dwb::Engine engine;
	engine.StartUp();

	engine.Get<dwb::Renderer>()->Create("GAT150", 800, 600);

	std::cout << dwb::GetFilePath() << std::endl;
	dwb::SetFilePath("../Resources");
	std::cout << dwb::GetFilePath() << std::endl;

	std::shared_ptr<dwb::Texture> texture = engine.Get<dwb::ResourceSystem>()->Get<dwb::Texture>("sf2.png", engine.Get<dwb::Renderer>());

	//CODE GO HERE


	bool quit = false;
	SDL_Event event;

	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Get<dwb::Renderer>()->BeginFrame();

		dwb::Vector2 pos{ 300,400 };
		engine.Get<dwb::Renderer>()->Draw(texture, pos);

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