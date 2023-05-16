#ifndef __HYPER_SOUND_SERVICE_H__
#define __HYPER_SOUND_SERVICE_H__

#include <string_view>

#include "hyper/fwd.h"

namespace hyper
{
	using SoundId = unsigned short;

	class ISoundService
	{
	public:
		virtual SoundId AddSound(std::string_view filepath) = 0;
		virtual void Play(SoundId id, float volume) const = 0;
		virtual ~ISoundService() = default;
	};

	class NullSoundService final : public ISoundService
	{
	public:
		SoundId AddSound(std::string_view) override { return 0; }
		void Play(SoundId, float) const override {}
	};

	class DefaultSoundService final : public ISoundService
	{
	public:
		DefaultSoundService();

		SoundId AddSound(std::string_view filepath) override;
		void Play(SoundId id, float volume) const override;

		DefaultSoundService(const DefaultSoundService&)				= delete;
		DefaultSoundService(DefaultSoundService&&)					= delete;
		DefaultSoundService& operator=(const DefaultSoundService&)	= delete;
		DefaultSoundService& operator=(DefaultSoundService&&)		= delete;

		~DefaultSoundService();

	private:
		class Impl;
		Impl* m_pImpl;
	};
}

#endif // !__HYPER_SOUND_SERVICE_H__
