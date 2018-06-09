#ifndef __LOSE_SCENE_H__
#define __LOSE_SCENE_H__

#include "cocos2d.h"

class LoseScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method maddnually
	CREATE_FUNC(LoseScene);
};

#endif // __Lose_SCENE_H__
