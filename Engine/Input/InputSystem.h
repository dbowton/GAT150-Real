#pragma once
#include "Framework/System.h"
#include "Math/Vector2.h"
#include "SDL.h"
#include <vector>
#include <array>


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

		enum class eMouseButton
		{
			Left,
			Middle,
			Right
		};

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id); 
		bool IsPreviousKeyDown(int id);

	public:
		void StartUp() override;
		void ShutDown() override;
		void Update(float dt) override;
	
		const Vector2& GetMousePosition() const { return mousePosition; }
		bool IsButtonDown(int id) { return mouseButtonState[id]; }
		bool IsPreviousButtonDown(int id) { return prevMouseButtonState[id]; }
		eKeyState GetButtonState(int id);

	private:
		std::vector<Uint8> keyboardState; 
		std::vector<Uint8> prevKeyboardState; 
		int numKeys;

		Vector2 mousePosition;
		std::array<Uint8, 3> mouseButtonState;
		std::array<Uint8, 3> prevMouseButtonState;
	};
}