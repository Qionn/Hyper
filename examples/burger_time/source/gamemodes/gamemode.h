#ifndef __BURGER_TIME_GAMEMODE_H__
#define __BURGER_TIME_GAMEMODE_H__

#include <hyper/fwd.h>

namespace burger_time
{
	class MapComponent;

	class IGamemode
	{
	public:
		virtual void Setup(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap) = 0;
		virtual ~IGamemode() = default;
	};
}

#endif // !__BURGER_TIME_GAMEMODE_H__
