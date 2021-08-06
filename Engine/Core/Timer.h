#pragma once
#include <chrono>

namespace dwb
{
	class Timer
	{
	public:
		using clock = std::chrono::high_resolution_clock;
		//using clock_dur = std::chrono::duration<clock::rep, std::milli>;
		using clock_dur = clock::duration;
		using clock_tick_ty = clock::rep;
	
	public:
		Timer() : timePoint{ clock::now() } {}

		void reset() { timePoint = clock::now(); }
		clock_tick_ty ElapsedTicks();
		float ElapsedSeconds();

	protected:
		clock::time_point timePoint;
	};

	class FrameTimer : public Timer
	{
	public:
		FrameTimer() : frameTimePoint{ clock::now() }, startTimePoint{clock::now()} {}
		void Tick();

	public:
		float timeScale{ 1 };
		float deltaTime{ 0 };
		float time{ 0 };

	private:
		clock::time_point frameTimePoint;
		clock::time_point startTimePoint;
	};
}