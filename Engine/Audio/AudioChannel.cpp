#include "AudioChannel.h"

namespace dwb
{
	bool AudioChannel::IsPlaying()
	{
		if (!channel) return false;

		bool isPlaying;
		channel->isPlaying(&isPlaying);
		
		return isPlaying;
	}
	
	void AudioChannel::Stop()
	{
		if (IsPlaying())
		{
			channel->stop();
		}

	}

	float AudioChannel::GetPitch()
	{
		float pitch = 0;
		if (IsPlaying())
		{
			channel->getPitch(&pitch);
		}
		return pitch;
	}

	void AudioChannel::SetPitch(float pitch)
	{
		if (IsPlaying())
		{
			channel->setPitch(pitch);
		}
	}

	float AudioChannel::GetVolume()
	{
		float volume = 0;
		if (IsPlaying())
		{
			channel->getPitch(&volume);
		}
		return volume;
	}

	void AudioChannel::SetVolume(float volume)
	{
		if (IsPlaying())
		{
			channel->setVolume(volume);
		}
	}
}