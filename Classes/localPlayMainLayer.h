#ifndef __LOCALPLAY_LAYER_H__
#define __LOCALPLAY_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "hero.h"
#include "localPlayStatusLayer.h"
#include "localPlayScene.h"
#include <map>
#include "Monster.h"


class localPlay : public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _heart;
	cocos2d::TMXLayer* _npc;
	Hero *hero;
	Monster *monster1;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyStatus;
	
public:
	//static cocos2d::Scene* createScene();
	localStatus* statusLayer;

	virtual bool init();
	virtual void onEnter();

	virtual void onPress(cocos2d::EventKeyboard::KeyCode keyCode);

	void getStatusLayer(localStatus* tLayer);
	cocos2d::EventKeyboard::KeyCode whichPressed();
	void update(float delta) override;

	bool detectPlayerPosition(cocos2d::Vec2 position);//检测Hero位置与地图某些地方的重合问题，返回是否可移动
	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);

	
	// implement the "static create()" method manually
	CREATE_FUNC(localPlay);
};

#endif // __LOCALPLAY_LAYER_H__
