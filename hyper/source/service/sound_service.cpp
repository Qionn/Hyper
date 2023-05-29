#if defined(HYPER_BACKEND_SDL2)
#	include "backend/sdl2/sdl2_sound_service.h"
#endif

#include "hyper/utils/logging.h"

namespace hyper
{
	DefaultSoundService::DefaultSoundService()
	{
		m_pImpl = new Impl();
	}

	DefaultSoundService::~DefaultSoundService()
	{
		delete m_pImpl;
	}

	SoundId DefaultSoundService::AddSound(std::string_view filepath)
	{
		return m_pImpl->AddSound(filepath);
	}

	void DefaultSoundService::Play(SoundId id, float volume) const
	{
		m_pImpl->Play(id, volume);
	}
}
