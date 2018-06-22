#ifndef __LOCALSCENE_SCENE_H__
#define __LOCALSCENE_SCENE_H__

#include "cocos2d.h"

class localScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	//void transPlayerName(const char* name);
	virtual bool init();

	// implement the "static create()" method maddnually
	CREATE_FUNC(localScene);
};

#endif // __LOCALSCENE_SCENE_H__
