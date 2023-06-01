#include "sdl2_audio_clip.h"

#include "hyper/utils/logging.h"

namespace hyper
{
	AudioClip::Impl::Impl(std::string_view filepath)
		: m_Filepath{ filepath }
	{
		
	}

	AudioClip::Impl::~Impl()
	{
		Unload();
	}

	void AudioClip::Impl::Load()
	{
		if (m_pSound == nullptr)
		{
			m_pSound = Mix_LoadWAV(m_Filepath.c_str());
			if (m_pSound == nullptr)
			{
				LogWarn("Failed to load audio clip '{}'", m_Filepath);
			}
		}
	}

	void AudioClip::Impl::Unload()
	{
		if (m_pSound != nullptr)
		{
			Mix_FreeChunk(m_pSound);
			m_pSound = nullptr;
		}
	}

	void AudioClip::Impl::Play(float volume) const
	{
		if (m_pSound != nullptr)
		{
			Mix_VolumeChunk(m_pSound, static_cast<int>(MIX_MAX_VOLUME * volume));

			if (Mix_PlayChannel(-1, m_pSound, 0) == -1)
			{
				LogWarn("Failed to play audio clip '{}'", m_Filepath);
			}
		}
	}

	bool AudioClip::Impl::IsLoaded() const
	{
		return m_pSound != nullptr;
	}
}
