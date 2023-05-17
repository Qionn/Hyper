#if defined(HYPER_PLATFORM_SDL2)
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

	LoggingSoundService::LoggingSoundService(std::unique_ptr<ISoundService>&& soundService)
		: m_SoundService{ std::move(soundService) }
	{
		
	}

	SoundId LoggingSoundService::AddSound(std::string_view filepath)
	{
		SoundId id = m_SoundService->AddSound(filepath);
		LogTrace("Added sound '{}' with id {}", filepath, id);
		return id;
	}

	void LoggingSoundService::Play(SoundId id, float volume) const
	{
		LogTrace("Playing sound {} with {:.0f}% volume", id, volume * 100);
		m_SoundService->Play(id, volume);
	}

}
