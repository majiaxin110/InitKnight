#ifndef __LOCALPLAY_LAYER_H__
#define __LOCALPLAY_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "hero.h"
#include "localPlayStatusLayer.h"
#include "localPlayScene.h"
#include <map>

class localPlay : public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _heart;
	Hero *hero;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyStatus;
	localStatus* statusLayer;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance Vec2er
	//static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void onEnter();

	virtual void onPress(cocos2d::EventKeyboard::KeyCode keyCode);

	void getStatusLayer(localStatus* tLayer);
	cocos2d::EventKeyboard::KeyCode whichPressed();
	void update(float delta) override;

	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);

	// implement the "static create()" method manually
	CREATE_FUNC(localPlay);
};

#endif // __LOCALPLAY_LAYER_H__
