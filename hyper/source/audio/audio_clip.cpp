#if defined(HYPER_PLATFORM_SDL2)
#	include "backend/sdl2/sdl2_audio_clip.h"
#endif

namespace hyper
{
	AudioClip::AudioClip(std::string_view filepath)
	{
		m_pImpl = new Impl(filepath);
	}

	AudioClip::~AudioClip()
	{
		delete m_pImpl;
	}

	void AudioClip::Load()
	{
		m_pImpl->Load();
	}

	void AudioClip::Unload()
	{
		m_pImpl->Unload();
	}

	void AudioClip::Play(float volume) const
	{
		m_pImpl->Play(volume);
	}

	bool AudioClip::IsLoaded() const
	{
		return m_pImpl->IsLoaded();
	}
}
