#ifndef __HYPER_TEXTURE_H__
#define __HYPER_TEXTURE_H__

#include <string_view>

namespace hyper
{
	class ITexture
	{
	public:
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual ~ITexture() = default;
	};
}

#endif // !__HYPER_TEXTURE_H__
