#ifndef __HYPER_RECT_H__
#define __HYPER_RECT_H__

#include <concepts>

namespace hyper
{
	template<class T> requires std::integral<T> || std::floating_point<T>
	struct Rect final
	{
		T x, y;
		T width, height;
	};

	using Rectf = Rect<float>;
	using Recti = Rect<int>;
}

#endif // !__HYPER_RECT_H__
