#ifndef __HYPER_SDL2_AUDIO_CLIP_H__
#define __HYPER_SDL2_AUDIO_CLIP_H__

#include <string>

#include <SDL_mixer.h>

#include "hyper/audio/audio_clip.h"

namespace hyper
{
	class AudioClip::Impl final
	{
	public:
		Impl(std::string_view filepath);

		void Load();
		void Unload();
		void Play(float volume) const;
		bool IsLoaded() const;

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl();

	private:
		const std::string m_Filepath;
		Mix_Chunk* m_pSound = nullptr;
	};
}

#endif // !__HYPER_SDL2_AUDIO_CLIP_H__
