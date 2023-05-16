#ifndef __BURGER_TIME_EXERCISE_LAYER_H__
#define __BURGER_TIME_EXERCISE_LAYER_H__

#include <hyper/core/layer.h>
#include <hyper/service/service_hub.h>

namespace burger_time
{
	class ExerciseLayer final : public hyper::ILayer
	{
	public:
		ExerciseLayer();

		void OnRender() override;

		ExerciseLayer(const ExerciseLayer&)				= delete;
		ExerciseLayer(ExerciseLayer&&)					= delete;
		ExerciseLayer& operator=(const ExerciseLayer&)	= delete;
		ExerciseLayer& operator=(ExerciseLayer&&)		= delete;

		~ExerciseLayer() = default;

	private:
		std::string m_TestSoundFilepath;
		hyper::SoundId m_TestSoundId;
		float m_Volume = 1.0f;
	};
}

#endif // !__BURGER_TIME_EXERCISE_LAYER_H__
