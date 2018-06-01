#ifndef __LOCALPLAY_SCENE_H__
#define __LOCALPLAY_SCENE_H__

#include "cocos2d.h"

class localPlay : public cocos2d::Scene
{
private:
	cocos2d::TMXTiledMap *tileMap;
	cocos2d::Sprite *player;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	// implement the "static create()" method manually
	CREATE_FUNC(localPlay);
};

#endif // __LOCALPLAY_SCENE_H__
