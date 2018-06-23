#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "hero.h"
#include "localPlayStatusLayer.h"
#include <map>
#include <vector>
#include "Monster.h"
#include "Bullet.h"
#include "SocketServer.h"  //服务器基础
#include "BaseLayer.h"  //存放一些发送传输数据时都要用到的
#include "ScoreScene.h"

USING_NS_CC;

class ServerLayer : public cocos2d::Layer
{
private:

	

public:
	
	void Place(float dt);  //临时定义的改变位置的函数

	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _heart;

	Hero *hero;
	Hero *hero2;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyStatus;

	SocketServer* _server;

	void initNetwork();
	void sendData(DataType type);
	void onRecv(HSocket socket, const char* data, int count);
	
	void addBullet();
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

	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);
	void setPlayerPosition(Vec2 position);
	std::vector<Bullet*> bulletVec;

	void changeToWin();
	void changeToLose();

	//std::vector<Monster*>& getMonsterVec();
	// implement the "static create()" method manually
	CREATE_FUNC(ServerLayer);
};