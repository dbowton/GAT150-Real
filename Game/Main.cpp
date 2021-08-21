#include "Game.h"

int main(int, char**)
{
	Game game;
	game.Initialize();

	rapidjson::Document document;
	bool success = dwb::json::Load("json.txt", document);
	assert(success);

	std::string str; dwb::json::Get(document, "string", str); 
	std::cout << str << std::endl;
	
	bool b; 
	dwb::json::Get(document, "boolean", b); 
	std::cout << b << std::endl;

	int i1; 
	dwb::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl; 

	int i2; 
	dwb::json::Get(document, "integer2", i2); 
	std::cout << i2 << std::endl; 

	float f; 
	dwb::json::Get(document, "float", f); 
	std::cout << f << std::endl;
	
	dwb::Vector2 v2; 
	dwb::json::Get(document, "vector2", v2); 
	std::cout << v2 << std::endl; 
	dwb::Color color; 
	dwb::json::Get(document, "color", color); 
	std::cout << color << std::endl;


	bool quit = false;
	SDL_Event event;

	while (!quit && !game.IsQuit())
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		game.Update();
		game.Draw();
	}

	SDL_Quit();
	return 0;
}