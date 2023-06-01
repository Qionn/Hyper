#ifndef __HYPER_TEXT_COMPONENT_H__
#define __HYPER_TEXT_COMPONENT_H__

#include <memory>
#include <string>

#include <glm/vec3.hpp>

#include "hyper/graphics/texture.h"
#include "hyper/scene/component.h"

namespace hyper
{
	class TextComponent final : public AComponent
	{
	public:
		TextComponent(Actor* pActor, std::string fontPath, int ptSize);

		void SetText(std::string_view text);
		void SetColor(const glm::vec3& color);

		const std::string& GetText() const;
		const glm::vec3& GetColor() const;
		int GetPointSize() const;

		void OnUpdate(float dt) override;
		void OnRender(const IContext& context) const override;

		~TextComponent() = default;

	private:
		std::string m_FontPath;
		glm::vec3 m_Color;
		int m_PointSize;

		std::string m_Text;
		bool m_IsDirty = false;

		std::unique_ptr<ITexture> m_pTexture;
	};
}

#endif // !__HYPER_TEXT_COMPONENT_H__
