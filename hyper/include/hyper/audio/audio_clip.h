#ifndef __HYPER_AUDIO_CLIP_H__
#define __HYPER_AUDIO_CLIP_H__

#include <string_view>

namespace hyper
{
	class AudioClip final
	{
	public:
		AudioClip(std::string_view filepath);

		void Load();
		void Unload();
		void Play(float volume) const;
		bool IsLoaded() const;

		AudioClip(const AudioClip&)				= delete;
		AudioClip(AudioClip&&)					= delete;
		AudioClip& operator=(const AudioClip&)	= delete;
		AudioClip& operator=(AudioClip&&)		= delete;

		~AudioClip();

	private:
		class Impl;
		Impl* m_pImpl;
	};
}

#endif // !__HYPER_AUDIO_CLIP_H__
