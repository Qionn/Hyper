#ifndef __BURGER_TIME_LEVEL_SCENE_H__
#define __BURGER_TIME_LEVEL_SCENE_H__

#include <string_view>

#include <hyper/fwd.h>

namespace burger_time
{
	void LoadLevelScene(hyper::Scene& scene, hyper::Input& input, std::string_view mapFile);
}

#endif // !__BURGER_TIME_LEVEL_SCENE_H__
