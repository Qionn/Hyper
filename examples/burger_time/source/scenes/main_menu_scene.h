#ifndef __BURGER_TIME_MAIN_MENU_SCENE_H__
#define __BURGER_TIME_MAIN_MENU_SCENE_H__

#include <hyper/service/service_hub.h>
#include <hyper/utils/command.h>
#include <hyper/fwd.h>

#include "components/menu_stack_component.h"

namespace burger_time
{
	class MenuActionCommand final : public hyper::ICommand
	{
	public:
		MenuActionCommand(MenuStackComponent* pMenuStack, IMenuState::Action action)
			: m_pMenuStack{ pMenuStack }, m_Action{ action } {}

		void Execute() override
		{
			m_pMenuStack->GetCurrentMenuState()->PerformAction(m_Action);
		}

	private:
		MenuStackComponent* m_pMenuStack;
		IMenuState::Action m_Action;
	};

	class MenuReturnCommand final : public hyper::ICommand
	{
	public:
		MenuReturnCommand(MenuStackComponent* pMenuStack)
			: m_pMenuStack{ pMenuStack }
		{
			hyper::ISoundService* pSoundService = hyper::ServiceHub::SoundService();
			m_SoundId = pSoundService->AddSound("assets/audio/menu_navigate_02.wav");
		}

		void Execute() override
		{
			hyper::ISoundService* pSoundService = hyper::ServiceHub::SoundService();
			pSoundService->Play(m_SoundId, 0.5f);
			m_pMenuStack->PopMenuState();
		}

	private:
		hyper::SoundId m_SoundId;
		MenuStackComponent* m_pMenuStack;
	};

	void LoadMainMenuScene(hyper::Scene& scene, hyper::Input& input);
}

#endif // !__BURGER_TIME_MAIN_MENU_SCENE_H__
