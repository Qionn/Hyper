#include "constants.h"
#include "menu_state.h"

#include "components/menu_fsm_component.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/actor.h>

#include <algorithm>

using namespace hyper;

namespace burger_time
{
	AMenuState::AMenuState(MenuFSMComponent* pMenuFSM, int fontSize, float spacing)
		: m_pMenuFSM{ pMenuFSM }
		, m_FontSize{ fontSize }
		, m_Spacing{ spacing }
	{
		m_pRootActor = m_pMenuFSM->GetActor().CreateChild();
		m_pRootActor->SetEnabled(false);

		SetupItemMarker();
	}

	void AMenuState::OnEnter()
	{
		m_pRootActor->SetEnabled(true);
	}

	void AMenuState::OnExit()
	{
		m_pRootActor->SetEnabled(false);
	}

	void AMenuState::SetCursor(size_t index)
	{
		m_CurrentItem = std::min(index, m_Items.size() - 1);
		m_pItemMarker->SetParent(m_Items[m_CurrentItem].pActor, false);
	}

	void AMenuState::MoveCursor(int32_t delta)
	{
		if (!m_Items.empty())
		{
			auto currentItem	= static_cast<int32_t>(m_CurrentItem);
			auto maxItem		= static_cast<int32_t>(m_Items.size() - 1);
			uint32_t nextItem	= std::clamp(currentItem - delta, 0, maxItem);

			if (m_CurrentItem != nextItem)
			{
				SetCursor(nextItem);
			}
		}
	}

	void AMenuState::Select() const
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

	Actor* AMenuState::GetRootActor() const
	{
		return m_pRootActor;
	}

	MenuFSMComponent* AMenuState::GetMenuFSM() const
	{
		return m_pMenuFSM;
	}

	void AMenuState::AddItem(std::string_view label, std::function<void()> onSelect)
	{
		Actor* pActor = m_pRootActor->CreateChild();
		auto pText = pActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, m_FontSize);
		pText->SetText(label);
		pText->SetColor({ 1, 1, 1 });

		if (m_Items.empty())
		{
			m_pItemMarker->SetEnabled(true);
			m_pItemMarker->SetParent(pActor, false);
		}
		else
		{
			pActor->SetParent(m_Items.back().pActor, false);
			pActor->SetPosition(0.0f, m_Spacing);
		}

		m_Items.push_back(Item{ pActor, std::move(onSelect) });
	}

	void AMenuState::SetupItemMarker()
	{
		m_pItemMarker = m_pRootActor->CreateChild();
		m_pItemMarker->SetEnabled(false);

		Actor* pActor1 = m_pItemMarker->CreateChild();
		pActor1->SetPosition(-200.0f, 0.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, m_FontSize);
		pText1->SetText(">");
		pText1->SetColor({ 1, 1, 1 });

		Actor* pActor2 = m_pItemMarker->CreateChild();
		pActor2->SetPosition(200.0f, 0.0f);
		auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, m_FontSize);
		pText2->SetText("<");
		pText2->SetColor({ 1, 1, 1 });
	}
}
