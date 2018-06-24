#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "hero.h"
#include "localPlayStatusLayer.h"
#include <string>
#include <map>
#include <vector>
#include "Monster.h"
#include "Bullet.h"
#include "SocketClient.h"
#include "BaseLayer.h"
#include "ScoreScene.h"
#include <string>

USING_NS_CC;



extern std::string targetIP;




class ClientLayer : public cocos2d::Layer
{
private:
	

public:
	


	void PlaceAndBlood(float dt);

	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _heart;

	Hero *hero;
	Hero *hero2;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyStatus;

	SocketClient* _client;

	Label* _lblInfo;

	void initNetwork();
	void sendData(DataType type);
	void onRecv(const char* data, int count);
	void onDisconnect();

	//static cocos2d::Scene* createScene();
	localStatus* statusLayer;

	virtual bool init();
	virtual void onEnter();
	//virtual void onExit();

	virtual void onPress(cocos2d::EventKeyboard::KeyCode keyCode);

	void getStatusLayer(localStatus* tLayer);
	cocos2d::EventKeyboard::KeyCode whichPressed();
	void update(float delta) override;

	bool detectPlayerPosition(cocos2d::Vec2 position);//检测Hero位置与地图某些地方的重合问题，返回是否可移动
	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);


	std::vector<Bullet*> bulletVec;

	void changeToWin();
	void changeToLose();

	//std::vector<Monster*>& getMonsterVec();
	// implement the "static create()" method manually
	CREATE_FUNC(ClientLayer);
};
