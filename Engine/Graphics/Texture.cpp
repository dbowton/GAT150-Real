#include "Texture.h"
#include "Graphics/Renderer.h"
#include "SDL_image.h"
#include <iostream>

namespace dwb
{
	bool Texture::Load(const std::string& name, void* data)
	{
		renderer = static_cast<Renderer*>(data)->renderer;

		SDL_Surface* surface = IMG_Load(name.c_str());
		if (!surface)
		{
			std::cout << "IMG_Load Error" << SDL_GetError() << std::endl;
			return false;
		}

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		if (!texture)
		{
			std::cout << "IMG_CreateTextureFromSurface Error" << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}
}