#ifndef _HITWORDS_SCENE_MANAGER_H_
#define _HITWORDS_SCENE_MANAGER_H_
#include "cocos2d.h"
using namespace cocos2d;
class HitWordsSceneManager {
public:
	Scene *loadScene;
	Scene *firstScene;
	Scene *menuScene;
	Scene *rankScene;
	Scene *aboutScene;
	Scene *helpScene;
	void CreateScene();
	void goLoad();
	void goFirst();
	void goMenu();
	void goRank();
	void goAbout();
	void goHelp();
};
#endif