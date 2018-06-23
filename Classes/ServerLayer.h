#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "hero.h"
#include "localPlayStatusLayer.h"
#include <map>
#include <vector>
#include "Monster.h"
#include "Bullet.h"
#include "SocketServer.h"  //����������
#include "BaseLayer.h"  //���һЩ���ʹ�������ʱ��Ҫ�õ���
#include "ScoreScene.h"

USING_NS_CC;

class ServerLayer : public cocos2d::Layer
{
private:

	

public:
	
	void Place(float dt);  //��ʱ����ĸı�λ�õĺ���

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

	bool detectPlayerPosition(cocos2d::Vec2 position);//���Heroλ�����ͼĳЩ�ط����غ����⣬�����Ƿ���ƶ�

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