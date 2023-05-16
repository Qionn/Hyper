#ifndef __HYPER_SDL2_SOUND_SERVICE_H__
#define __HYPER_SDL2_SOUND_SERVICE_H__

#include <atomic>
#include <condition_variable>
#include <memory>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

#include "hyper/audio/audio_clip.h"
#include "hyper/service/sound_service.h"

namespace hyper
{
	class DefaultSoundService::Impl final
	{
	public:
		Impl();

		SoundId AddSound(std::string_view filepath);
		void Play(SoundId id, float volume);

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl();

	private:
		struct PlayInfo
		{
			SoundId id;
			float volume;
		};

		std::vector<std::unique_ptr<AudioClip>> m_AudioClips;
		std::unordered_map<std::string, SoundId> m_SoundIdMap;

		std::queue<PlayInfo> m_SoundQueue;

		std::jthread m_Thread;
		std::mutex m_Mutex;
		std::condition_variable m_Conditional;
		std::atomic_bool m_JoinThread = false;

		static inline size_t s_InstanceCount = 0;

	private:
		void ThreadFunction();
	};
}

#endif // !__HYPER_SDL2_SOUND_SERVICE_H__
