#ifndef __HYPER_RENDERER_H__
#define __HYPER_RENDERER_H__

#include "hyper/fwd.h"

namespace hyper
{
	class Renderer final
	{
	public:
		Renderer(const Window& window);

		void BeginFrame();
		void EndFrame();

		IContext& GetContext() const;

		Renderer(const Renderer&)				= delete;
		Renderer(Renderer&&)					= delete;
		Renderer& operator=(const Renderer&)	= delete;
		Renderer& operator=(Renderer&&)			= delete;

		~Renderer();

	private:
		class Impl;
		Impl* m_pImpl;
	};
}

#endif // !__HYPER_RENDERER_H__
