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

			auto pAudioClip = m_AudioClips[info.id].get();

			lock.unlock();

			if (!pAudioClip->IsLoaded())
			{
				pAudioClip->Load();
			}

			pAudioClip->Play(info.volume);
		}
	}
}
