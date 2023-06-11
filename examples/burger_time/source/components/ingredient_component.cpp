#include "ingredient_component.h"

#include "components/player_component.h"

#include <hyper/event/dispatcher.h>
#include <hyper/scene/components/collider_component.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/scene.h>
#include <hyper/utils/assert.h>

#include <algorithm>

using namespace hyper;

namespace burger_time
{
	IngredientComponent::IngredientComponent(Actor& actor, IngredientType type, MapComponent* pMap)
		: AComponent(actor)
		, m_pMap{ pMap }
		, m_Type{ type }
		, m_SliceFlags{ false }
	{
		m_pPlatform = m_pMap->GetNearestPlatform(actor.GetWorldPosition(), FLT_MAX);
		HyperAssert(m_pPlatform != nullptr, "No near platform was found");
		ClampPositionToPlatform(*m_pPlatform);
		SpawnSlices();

		GetScene().GetPhysicsWorld().AddObserver(this);
	}

	IngredientComponent::~IngredientComponent()
	{
		GetScene().GetPhysicsWorld().RemoveObserver(this);
	}

	void IngredientComponent::Drop()
	{
		if (m_pPlatform != nullptr)
		{
			m_pPlatform = nullptr;
			m_SliceFlags.fill(false);

			for (Actor* pSlice : m_Slices)
			{
				glm::vec2 pos = pSlice->GetLocalPosition();
				pos.y = 0.0f;
				pSlice->SetPosition(pos);
			}

			GetActor().Translate(0.0f, 5.0f);
		}
	}

	bool IngredientComponent::IsOnPlatform() const
	{
		return m_pPlatform != nullptr;
	}

	bool IngredientComponent::IsInCatcher() const
	{
		return m_IsInCatcher;
	}

	void IngredientComponent::SpawnSlices()
	{
		Actor& actor = GetActor();

		for (size_t i = 0; i < m_Slices.size(); ++i)
		{
			Actor* pActor = actor.CreateChild();
			auto pSprite = pActor->AddComponent<SpriteComponent>(GetSpritePath());

			float halfWidth = pSprite->GetWidth() * 0.5f;
			float sliceWidth = pSprite->GetWidth() / m_Slices.size();
			float halfSliceWidth = sliceWidth * 0.5f;

			Recti clipRect;
			clipRect.x = static_cast<int>(sliceWidth * i);
			clipRect.y = 0;
			clipRect.width = static_cast<int>(sliceWidth);
			clipRect.height = static_cast<int>(pSprite->GetHeight());

			pSprite->SetClipRect(clipRect);

			pActor->AddComponent<ColliderComponent>(sliceWidth, pSprite->GetHeight());

			glm::vec2 pos;
			pos.x = (-halfWidth + halfSliceWidth) + (sliceWidth * i);
			pos.y = 0;

			pActor->SetPosition(pos);

			m_Slices[i] = pActor;
		}
	}

	void IngredientComponent::ClampPositionToPlatform(const Platform& platform)
	{
		Actor& actor = GetActor();

		glm::vec2 pos = actor.GetWorldPosition();

		pos.x = std::clamp(pos.x, platform.minX, platform.maxX);
		pos.y = platform.height;

		actor.SetPosition(pos);
	}

	void IngredientComponent::ClampPositionToCatcher(const Catcher& catcher)
	{
		Actor& actor = GetActor();

		glm::vec2 pos = actor.GetWorldPosition();

		pos.x = catcher.posX;
		pos.y = catcher.posY - 15.0f;

		actor.SetPosition(pos);
	}

	std::string_view IngredientComponent::GetSpritePath() const
	{
		switch (m_Type)
		{
			case IngredientType::eBunTop:		return "assets/sprites/ingredient_bun_top.png";
			case IngredientType::eBunBottom:	return "assets/sprites/ingredient_bun_bottom.png";
			case IngredientType::eCheese:		return "assets/sprites/ingredient_cheese.png";
			case IngredientType::ePatty:		return "assets/sprites/ingredient_patty.png";
			case IngredientType::eTomato:		return "assets/sprites/ingredient_tomato.png";
			case IngredientType::eLetuce:		return "assets/sprites/ingredient_letuce.png";
		}

		HyperAssert(false, "Invalid ingredient type");
		return nullptr;
	}

	void IngredientComponent::OnUpdate(float dt)
	{
		if (m_pPlatform == nullptr && !m_IsInCatcher)
		{
			Actor& actor = GetActor();

			actor.Translate(0.0f, m_Speed * dt);

			m_pPlatform = m_pMap->GetNearestPlatform(actor.GetWorldPosition(), 3.0f);
			if (m_pPlatform != nullptr)
			{
				ClampPositionToPlatform(*m_pPlatform);
			}

			const Catcher* pCatcher = m_pMap->GetNearestCatcher(actor.GetWorldPosition(), 3.0f);
			if (pCatcher != nullptr)
			{
				m_IsInCatcher = true;
				ClampPositionToCatcher(*pCatcher);
			}
		}
	}

	void IngredientComponent::OnRender(const IContext&) const
	{

	} 

	bool IngredientComponent::OnEvent(const AEvent& event)
	{
		Dispatcher dispatcher(event);

		dispatcher.Dispatch(&IngredientComponent::HandleSliceCollision, this);
		dispatcher.Dispatch(&IngredientComponent::HandleIngredientCollision, this);

		return dispatcher.IsEventHandled();
	}

	bool IngredientComponent::HandleSliceCollision(const hyper::OverlapBeginEvent& event)
	{
		for (size_t i = 0; i < m_Slices.size(); ++i)
		{
			Actor* pSlice = m_Slices[i];
			Actor* pOther = nullptr;

			if (event.IsInvolved(pSlice, pOther) && !m_SliceFlags[i])
			{
				if (auto pPlayer = pOther->GetComponent<PlayerComponent>(); pPlayer != nullptr)
				{
					pSlice->Translate(0.0f, 5.0f);
					m_SliceFlags[i] = true;
				}
			}
		}

		if (std::ranges::all_of(m_SliceFlags, [](bool flag) { return flag; }))
		{
			Drop();
		}

		return false;
	}

	bool IngredientComponent::HandleIngredientCollision(const hyper::OverlapBeginEvent& event)
	{
		Actor* pOwner = &GetActor();
		Actor* pOther = nullptr;

		if (event.IsInvolved(pOwner, pOther))
		{
			auto pIngredient = pOther->GetComponent<IngredientComponent>();
			if (pIngredient != nullptr && pIngredient != this)
			{
				if (pIngredient->IsInCatcher() && !m_IsInCatcher)
				{
					glm::vec2 pos = pOther->GetWorldPosition();
					pos.y -= 25.0f;
					pOwner->SetPosition(pos);
					m_IsInCatcher = true;
				}

				pIngredient->Drop();
			}
		}

		return false;
	}
}
