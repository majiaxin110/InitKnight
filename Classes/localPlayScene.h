#ifndef __LOCALPLAY_SCENE_H__
#define __LOCALPLAY_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "hero.h"
#include "bloodProgress.h"
#include <map>

class localPlay : public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _heart;
	Hero *hero;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyStatus;
	ProgressView *m_pProgressView;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance Vec2er
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	//virtual void onEnter();

	virtual void onPress(cocos2d::EventKeyboard::KeyCode keyCode);

	cocos2d::EventKeyboard::KeyCode whichPressed();
	void update(float delta) override;

	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);

	// implement the "static create()" method manually
	CREATE_FUNC(localPlay);
};

#endif // __LOCALPLAY_SCENE_H__
