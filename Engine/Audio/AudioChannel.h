#pragma once
#include "fmod.hpp"

namespace dwb
{
	class AudioChannel
	{
	public:
		AudioChannel() {}
		AudioChannel(FMOD::Channel* channel) : channel{ channel } {}

		bool IsPlaying();
		void Stop();

		float GetPitch();
		void SetPitch(float pitch);


		float GetVolume();
		void SetVolume(float volume);

	private:
		FMOD::Channel* channel{nullptr};
	};
}