#ifndef __HYPER_LAYER_STACK_H__
#define __HYPER_LAYER_STACK_H__

#include <concepts>
#include <memory>
#include <vector>

#include "hyper/core/layer.h"

namespace hyper
{
	class LayerStack final
	{
	public:
		LayerStack() = default;

		void Render();

		template<class T, class ... Args> requires std::derived_from<T, ILayer>
		void Push(Args&&... args)
		{
			m_Layers.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
		}

		void Pop();

		LayerStack(const LayerStack&)				= delete;
		LayerStack(LayerStack&&)					= delete;
		LayerStack& operator=(const LayerStack&)	= delete;
		LayerStack& operator=(LayerStack&&)			= delete;

		~LayerStack() = default;

	private:
		std::vector<std::unique_ptr<ILayer>> m_Layers;
	};
}

#endif // !__HYPER_LAYER_STACK_H__
