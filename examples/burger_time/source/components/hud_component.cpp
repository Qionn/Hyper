#include "constants.h"
#include "hud_component.h"

#include "scenes/end_scene.h"

#include <hyper/event/dispatcher.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

#include <format>

using namespace hyper;

namespace burger_time
{
	HUDComponent::HUDComponent(Actor& actor, int numLives, int numBurgers)
		: AComponent(actor)
		, m_NumBurgers{ numBurgers }
	{
		ISoundService* pSound = ServiceHub::SoundService();
		m_PlayerHitSoundId = pSound->AddSound("assets/audio/pepper_hit.wav");
		m_IngredientDropSoundId = pSound->AddSound("assets/audio/ingredient_drop.wav");
		m_IngredientSliceSoundId = pSound->AddSound("assets/audio/ingredient_walk.wav");

		CreateLives(numLives);
		CreateScore();
	}

	int HUDComponent::GetRemainingLives() const
	{
		return static_cast<int>(m_LiveActors.size());
	}

	void HUDComponent::OnUpdate(float)
	{

	}

	void HUDComponent::OnRender(const IContext&) const
	{

	}

	bool HUDComponent::OnEvent(const hyper::AEvent& event)
	{
		Dispatcher dispatcher(event);

		dispatcher.Dispatch(&HUDComponent::OnPlayerHitEvent, this);
		dispatcher.Dispatch(&HUDComponent::OnIngredientDropEvent, this);
		dispatcher.Dispatch(&HUDComponent::OnIngredientSliceEvent, this);
		dispatcher.Dispatch(&HUDComponent::OnBurgerCompleteEvent, this);

		return dispatcher.IsEventHandled();
	}

	bool HUDComponent::OnPlayerHitEvent(const PlayerHitEvent&)
	{
		if (m_LiveActors.size() > 0)
		{
			ISoundService* pSound = ServiceHub::SoundService();
			pSound->Play(m_PlayerHitSoundId, 0.5f);

			Actor* pActor = m_LiveActors.back();
			GetScene().RemoveActor(pActor);
			m_LiveActors.pop_back();
			
			m_Score -= 100;
			UpdateScore();
		}

		if (m_LiveActors.empty())
		{
			EndLevel(true);
		}

		return false;
	}

	bool HUDComponent::OnIngredientDropEvent(const IngredientDropEvent&)
	{
		ISoundService* pSound = ServiceHub::SoundService();
		pSound->Play(m_IngredientDropSoundId, 0.5f);

		m_Score += 50;
		UpdateScore();

		return false;
	}

	bool HUDComponent::OnIngredientSliceEvent(const IngredientSliceEvent&)
	{
		ISoundService* pSound = ServiceHub::SoundService();
		pSound->Play(m_IngredientSliceSoundId, 0.5f);

		m_Score += 50;
		UpdateScore();

		return false;
	}

	bool HUDComponent::OnBurgerCompleteEvent(const BurgerCompleteEvent&)
	{
		if (--m_NumBurgers == 0)
		{
			EndLevel(false);
		}

		return false;
	}

	void HUDComponent::CreateLives(int numLives)
	{
		Actor& root = GetActor();
		glm::vec2 pos(20.0f, 770.0f);
		constexpr float spacing = 40.0f;

		for (int i = 0; i < numLives; ++i)
		{
			Actor* pActor = root.CreateChild();
			pActor->SetPosition(pos);
			pActor->AddComponent<SpriteComponent>("assets/sprites/hud_live.png");
			pos.y -= spacing;
			m_LiveActors.push_back(pActor);
		}
	}

	void HUDComponent::CreateScore()
	{
		Actor& root = GetActor();

		Actor* pActor = root.CreateChild();
		pActor->SetPosition(90.0f, 25.0f);
		auto pText = pActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 36);
		pText->SetColor({ 1, 0, 0 });
		pText->SetText("Score");

		m_pScoreActor = pActor->CreateChild();
		m_pScoreActor->SetPosition(0.0f, 40.0f);
		auto pText2 = m_pScoreActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 36);
		pText2->SetColor({ 1, 1, 1 });

		UpdateScore();
	}

	void HUDComponent::UpdateScore()
	{
		auto pText = m_pScoreActor->GetComponent<TextComponent>();
		std::string score = std::format("{:05}", m_Score);
		pText->SetText(score);
	}

	void HUDComponent::EndLevel(bool playerDied) const
	{
		using namespace std::placeholders;
		Scene& scene = GetScene();
		scene.RequestLoad(std::bind(&LoadEndScene, _1, _2, m_Score, playerDied));
	}
}
