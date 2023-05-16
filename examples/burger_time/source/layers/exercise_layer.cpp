#include "exercise_layer.h"

#include <imgui.h>

using namespace hyper;

namespace burger_time
{
	ExerciseLayer::ExerciseLayer()
		: m_TestSoundFilepath{ "assets/sounds/test_sound.wav" }
	{
		m_TestSoundId = ServiceHub::SoundService()->AddSound(m_TestSoundFilepath);
	}

	void ExerciseLayer::OnRender()
	{
		if (ImGui::Begin("Sound Panel"))
		{
			if (ImGui::Button("Play"))
			{
				ServiceHub::SoundService()->Play(m_TestSoundId, m_Volume);
			}

			ImGui::SameLine();
			ImGui::TextUnformatted(m_TestSoundFilepath.c_str());

			ImGui::SliderFloat("Volume", &m_Volume, 0.0f, 1.0f);
		}
		ImGui::End();
	}
}
