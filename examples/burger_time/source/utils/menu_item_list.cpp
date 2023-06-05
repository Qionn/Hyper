#include "constants.h"
#include "menu_item_list.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>
#include <hyper/service/service_hub.h>

#include <algorithm>

using namespace hyper;

namespace burger_time
{
	MenuItemList::MenuItemList(Actor* pRootActor, int ptSize, float spacing)
		: m_PointSize{ ptSize }
		, m_Spacing{ spacing }
		, m_pRootActor{ pRootActor }
	{
		ISoundService* pSoundService = ServiceHub::SoundService();
		m_SoundId = pSoundService->AddSound("assets/audio/menu_navigate_01.wav");

		SetupItemMarker();
	}

	void MenuItemList::MoveCursor(int32_t delta)
	{
		if (!m_Items.empty())
		{
			auto maxItem = static_cast<int>(m_Items.size() - 1);
			int nextItem = std::clamp(m_CurrentItem - delta, 0, maxItem);

			if (m_CurrentItem != nextItem)
			{
				ISoundService* pSoundService = ServiceHub::SoundService();
				pSoundService->Play(m_SoundId, 0.5f);

				m_CurrentItem = nextItem;
				m_pItemMarker->SetParent(m_Items[m_CurrentItem].pActor, false);
			}
		}
	}

	void MenuItemList::Select() const
	{
		if (!m_Items.empty())
		{
			const Item& item = m_Items[m_CurrentItem];
			if (item.onSelect != nullptr)
			{
				item.onSelect();
			}
		}
	}

	void MenuItemList::AddItem(std::string_view label, std::function<void()> onSelect)
	{
		Scene& scene = m_pRootActor->GetScene();

		Actor* pActor = scene.CreateActor();
		auto pText = pActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, m_PointSize);
		pText->SetText(label);
		pText->SetColor({ 1, 1, 1 });

		if (m_Items.empty())
		{
			pActor->SetParent(m_pRootActor, false);
			m_pItemMarker->SetEnabled(true);
			m_pItemMarker->SetParent(pActor, false);
		}
		else
		{
			pActor->SetParent(m_Items.back().pActor, false);
			pActor->SetPosition(0.0f, m_Spacing);
		}

		m_Items.emplace_back(pActor, std::move(onSelect));
	}

	void MenuItemList::SetupItemMarker()
	{
		Scene& scene = m_pRootActor->GetScene();

		m_pItemMarker = scene.CreateActor();
		m_pItemMarker->SetEnabled(false);

		Actor* pActor1 = scene.CreateActor();
		pActor1->SetParent(m_pItemMarker, false);
		pActor1->SetPosition(-200.0f, 0.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, m_PointSize);
		pText1->SetText(">");
		pText1->SetColor({ 1, 1, 1 });

		Actor* pActor2 = scene.CreateActor();
		pActor2->SetParent(m_pItemMarker, false);
		pActor2->SetPosition(200.0f, 0.0f);
		auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, m_PointSize);
		pText2->SetText("<");
		pText2->SetColor({ 1, 1, 1 });
	}
}
