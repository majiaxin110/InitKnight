#ifndef __LOCALPLAY_LAYER_H__
#define __LOCALPLAY_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "hero.h"
#include "localPlayStatusLayer.h"
#include "localPlayScene.h"
#include <map>
#include <vector>
#include "Monster.h"
#include "Bullet.h"
//#include "Weapon.h"


class localPlay : public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _heart;
	cocos2d::TMXLayer* _npc;
	cocos2d::TMXLayer* _diamond;
	cocos2d::TMXLayer* _speed;
	cocos2d::TMXLayer* _end;
	Hero *hero;
	
	//Bullet *
	//Weapon *weapon;
	//Vector<Bullet*> bullet;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyStatus;
	
public:
	//static cocos2d::Scene* createScene();
	localStatus* statusLayer;

	virtual bool init();
	virtual void onEnter();
	//virtual void onExit();

	virtual void onPress(cocos2d::EventKeyboard::KeyCode keyCode);

	void getStatusLayer(localStatus* tLayer);
	cocos2d::EventKeyboard::KeyCode whichPressed();
	void update(float delta) override;

	bool detectPlayerPosition(cocos2d::Vec2 position);//���Heroλ�����ͼĳЩ�ط����غ����⣬�����Ƿ���ƶ�
	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);

	std::vector<Monster*> monsterVec;
	std::vector<Bullet*> bulletVec;

	//std::vector<Monster*>& getMonsterVec();
	// implement the "static create()" method manually
	CREATE_FUNC(localPlay);
};

#endif // __LOCALPLAY_LAYER_H__
