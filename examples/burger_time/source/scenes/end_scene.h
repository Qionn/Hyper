#ifndef __BURGER_TIME_END_SCENE_H__
#define __BURGER_TIME_END_SCENE_H__

#include <hyper/fwd.h>

namespace burger_time
{
	void LoadEndScene(hyper::Scene& scene, hyper::Input& input, int score, bool playerDied);

	void SaveLocalHighScore(int score);
	int GetLocalHighScore();
}

#endif // !__BURGER_TIME_END_SCENE_H__
