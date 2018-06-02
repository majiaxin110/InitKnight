#ifndef __LOCALPLAY_SCENE_H__
#define __LOCALPLAY_SCENE_H__

#include "cocos2d.h"
#include "hero.h"
#include <map>

class localPlay : public cocos2d::Scene
{
private:
	cocos2d::TMXTiledMap *tileMap;
	cocos2d::TMXLayer *barriers;//障碍物
	cocos2d::Sprite *player;
	Hero* hero;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyStatus; //键盘各个按键被按下的状态
public:
	

	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();

	cocos2d::EventKeyboard::KeyCode whichPressed(); //哪个键当前是按下状态
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 pos); //转换瓦片坐标
	bool isCollid(cocos2d::Vec2 pos);//检测是否与地图墙壁碰撞
	void setHero(cocos2d::EventKeyboard::KeyCode keyCode);//控制hero
	void update(float delta) override;

	// implement the "static create()" method manually
	CREATE_FUNC(localPlay);
};

#endif // __LOCALPLAY_SCENE_H_
