#include "hyper/utils/layer_stack.h"

namespace hyper
{
	void LayerStack::Render()
	{
		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnRender();
		}
	}

	void LayerStack::Pop()
	{
		m_Layers.pop_back();
	}
}
