#ifndef __HYPER_LAYER_H__
#define __HYPER_LAYER_H__

namespace hyper
{
	class ILayer
	{
	public:
		virtual void OnRender() = 0;
		virtual ~ILayer() = default;
	};
}

#endif // !__HYPER_LAYER_H__
