#pragma once
#include "Framework/System.h"
#include "SDL.h"
#include <vector>


namespace dwb
{
	class InputSystem : public System
	{
	public:
		enum class eKeyState
		{
			Idle,
			Pressed,
			Held,
			Release
		};

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id); 
		bool IsPreviousKeyDown(int id);

	public:
		void StartUp() override;
		void ShutDown() override;
		void Update(float dt) override;
	
	private:
		std::vector<Uint8> keyboardState; 
		std::vector<Uint8> prevKeyboardState; 
		int numKeys;
	};
}