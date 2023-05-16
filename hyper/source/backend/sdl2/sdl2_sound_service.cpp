#include "sdl2_sound_service.h"

#include <SDL_mixer.h>

namespace hyper
{
	DefaultSoundService::Impl::Impl()
	{
		if (s_InstanceCount++ == 0)
		{
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		}

		m_Thread = std::jthread(&Impl::ThreadFunction, this);
	}

	DefaultSoundService::Impl::~Impl()
	{
		m_JoinThread = true;
		m_Conditional.notify_all();
		m_Thread.join();

		if (--s_InstanceCount == 0)
		{
			Mix_CloseAudio();
		}
	}

	SoundId DefaultSoundService::Impl::AddSound(std::string_view filepath)
	{
		auto id = static_cast<SoundId>(m_AudioClips.size());
		m_SoundIdMap[std::string(filepath)] = id;

		{
			std::lock_guard lock(m_Mutex);
			m_AudioClips.emplace_back(std::make_unique<AudioClip>(filepath));
		}

		return id;
	}

	void DefaultSoundService::Impl::Play(SoundId id, float volume)
	{
		{
			std::lock_guard lock(m_Mutex);
			m_SoundQueue.push({ id, volume });
		}

		m_Conditional.notify_one();
	}

	void DefaultSoundService::Impl::ThreadFunction()
	{
		while (true)
		{
			std::unique_lock lock(m_Mutex);
			m_Conditional.wait(lock, [this]() { return !m_SoundQueue.empty() || m_JoinThread; });

			if (m_SoundQueue.empty() && m_JoinThread)
			{
				break;
			}

			auto info = m_SoundQueue.front();
			m_SoundQueue.pop();

			const auto& audioClip = m_AudioClips[info.id];

			if (!audioClip->IsLoaded())
			{
				audioClip->Load();
			}

			audioClip->Play(info.volume);
		}
	}
}