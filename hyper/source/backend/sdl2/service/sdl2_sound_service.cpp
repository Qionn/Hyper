#include "sdl2_sound_service.h"

#include <SDL.h>
#include <SDL_mixer.h>

namespace hyper
{
	DefaultSoundService::Impl::Impl()
	{
		if (s_InstanceCount++ == 0)
		{
			if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
			{
				throw std::runtime_error("Failed to initialize SDL2 audio subsystem");
			}

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
			{
				throw std::runtime_error("Failed to open SDL2 Mixer audio");
			}
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
			SDL_QuitSubSystem(SDL_INIT_AUDIO);
		}
	}

	SoundId DefaultSoundService::Impl::AddSound(std::string_view filepath)
	{
		std::string strFilepath(filepath);

		auto it = m_SoundIdMap.find(strFilepath);
		if (it != m_SoundIdMap.end())
		{
			return it->second;
		}

		auto id = static_cast<SoundId>(m_AudioClips.size());
		m_SoundIdMap[strFilepath] = id;

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

	void DefaultSoundService::Impl::Mute()
	{
		m_IsMuted = true;
		Mix_MasterVolume(0);
	}

	void DefaultSoundService::Impl::Unmute()
	{
		m_IsMuted = false;
		Mix_MasterVolume(MIX_MAX_VOLUME);
	}

	bool DefaultSoundService::Impl::IsMuted()
	{
		return m_IsMuted;
	}

	void DefaultSoundService::Impl::ThreadFunction()
	{
		while (true)
		{
			std::unique_lock lock(m_Mutex);
			m_Conditional.wait(lock, [this]() { return !m_SoundQueue.empty() || m_JoinThread; });

			if (m_JoinThread)
			{
				break;
			}

			auto [id, volume] = m_SoundQueue.front();
			m_SoundQueue.pop();

			auto pAudioClip = m_AudioClips[id].get();

			lock.unlock();

			if (!pAudioClip->IsLoaded())
			{
				pAudioClip->Load();
			}

			pAudioClip->Play(volume);
		}
	}
}
