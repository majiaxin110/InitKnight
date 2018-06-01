#ifndef __LOCALPLAY_SCENE_H__
#define __LOCALPLAY_SCENE_H__

#include "cocos2d.h"
#include "hero.h"
#include <map>

class localPlay : public cocos2d::Scene
{
private:
	cocos2d::TMXTiledMap *tileMap;
	cocos2d::Sprite *player;
	Hero* hero;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyStatus; //键盘各个按键被按下的状态
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	cocos2d::EventKeyboard::KeyCode whichPressed();
	void update(float delta) override;
	// implement the "static create()" method manually
	CREATE_FUNC(localPlay);
};

#endif // __LOCALPLAY_SCENE_H__
